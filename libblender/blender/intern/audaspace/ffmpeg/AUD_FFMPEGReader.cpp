/*
 * $Id: AUD_FFMPEGReader.cpp 36960 2011-05-27 23:33:40Z schlaile $
 *
 * ***** BEGIN GPL LICENSE BLOCK *****
 *
 * Copyright 2009-2011 Jörg Hermann Müller
 *
 * This file is part of AudaSpace.
 *
 * Audaspace is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * AudaSpace is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Audaspace; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * ***** END GPL LICENSE BLOCK *****
 */

/** \file audaspace/ffmpeg/AUD_FFMPEGReader.cpp
 *  \ingroup audffmpeg
 */


// needed for INT64_C
#ifndef __STDC_CONSTANT_MACROS
#define __STDC_CONSTANT_MACROS
#endif

#include "AUD_FFMPEGReader.h"

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include "ffmpeg_compat.h"
}

int AUD_FFMPEGReader::decode(AVPacket* packet, AUD_Buffer& buffer)
{
	// save packet parameters
	uint8_t *audio_pkg_data = packet->data;
	int audio_pkg_size = packet->size;

	int buf_size = buffer.getSize();
	int buf_pos = 0;

	int read_length, data_size;

	AVPacket tmp_pkt;
	
	av_init_packet(&tmp_pkt);

	// as long as there is still data in the package
	while(audio_pkg_size > 0)
	{
		// resize buffer if needed
		if(buf_size - buf_pos < AVCODEC_MAX_AUDIO_FRAME_SIZE)
		{
			buffer.resize(buf_size + AVCODEC_MAX_AUDIO_FRAME_SIZE, true);
			buf_size += AVCODEC_MAX_AUDIO_FRAME_SIZE;
		}

		// read samples from the packet
		data_size = buf_size - buf_pos;

		tmp_pkt.data = audio_pkg_data;
		tmp_pkt.size = audio_pkg_size;

		read_length = avcodec_decode_audio3(
			m_codecCtx,
			(int16_t*)(((data_t*)buffer.getBuffer()) + buf_pos),
			&data_size, &tmp_pkt);

		// read error, next packet!
		if(read_length < 0)
			break;

		buf_pos += data_size;

		// move packet parameters
		audio_pkg_data += read_length;
		audio_pkg_size -= read_length;
	}

	return buf_pos;
}

static const char* streaminfo_error = "AUD_FFMPEGReader: Stream info couldn't "
									  "be found.";
static const char* noaudio_error = "AUD_FFMPEGReader: File doesn't include an "
								   "audio stream.";
static const char* nodecoder_error = "AUD_FFMPEGReader: No decoder found for "
									 "the audio stream.";
static const char* codecopen_error = "AUD_FFMPEGReader: Codec couldn't be "
									 "opened.";
static const char* format_error = "AUD_FFMPEGReader: Unsupported sample "
								  "format.";

void AUD_FFMPEGReader::init()
{
	m_position = 0;
	m_pkgbuf_left = 0;

	if(av_find_stream_info(m_formatCtx)<0)
		AUD_THROW(AUD_ERROR_FFMPEG, streaminfo_error);

	// find audio stream and codec
	m_stream = -1;

	for(unsigned int i = 0; i < m_formatCtx->nb_streams; i++)
	{
		if((m_formatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO)
			&& (m_stream < 0))
		{
			m_stream=i;
			break;
		}
	}

	if(m_stream == -1)
		AUD_THROW(AUD_ERROR_FFMPEG, noaudio_error);

	m_codecCtx = m_formatCtx->streams[m_stream]->codec;

	// get a decoder and open it
	AVCodec *aCodec = avcodec_find_decoder(m_codecCtx->codec_id);
	if(!aCodec)
		AUD_THROW(AUD_ERROR_FFMPEG, nodecoder_error);

	if(avcodec_open(m_codecCtx, aCodec)<0)
		AUD_THROW(AUD_ERROR_FFMPEG, codecopen_error);

	// XXX this prints file information to stdout:
	//dump_format(m_formatCtx, 0, NULL, 0);

	m_specs.channels = (AUD_Channels) m_codecCtx->channels;

	switch(m_codecCtx->sample_fmt)
	{
	case SAMPLE_FMT_U8:
		m_convert = AUD_convert_u8_float;
		m_specs.format = AUD_FORMAT_U8;
		break;
	case SAMPLE_FMT_S16:
		m_convert = AUD_convert_s16_float;
		m_specs.format = AUD_FORMAT_S16;
		break;
	case SAMPLE_FMT_S32:
		m_convert = AUD_convert_s32_float;
		m_specs.format = AUD_FORMAT_S32;
		break;
	case SAMPLE_FMT_FLT:
		m_convert = AUD_convert_copy<float>;
		m_specs.format = AUD_FORMAT_FLOAT32;
		break;
	case SAMPLE_FMT_DBL:
		m_convert = AUD_convert_double_float;
		m_specs.format = AUD_FORMAT_FLOAT64;
		break;
	default:
		AUD_THROW(AUD_ERROR_FFMPEG, format_error);
	}

	m_specs.rate = (AUD_SampleRate) m_codecCtx->sample_rate;
}

static const char* fileopen_error = "AUD_FFMPEGReader: File couldn't be "
									"opened.";

AUD_FFMPEGReader::AUD_FFMPEGReader(std::string filename) :
	m_pkgbuf(AVCODEC_MAX_AUDIO_FRAME_SIZE<<1),
	m_byteiocontext(NULL),
	m_membuf(NULL)
{
	// open file
	if(av_open_input_file(&m_formatCtx, filename.c_str(), NULL, 0, NULL)!=0)
		AUD_THROW(AUD_ERROR_FILE, fileopen_error);

	try
	{
		init();
	}
	catch(AUD_Exception&)
	{
		av_close_input_file(m_formatCtx);
		throw;
	}
}

static const char* streamopen_error = "AUD_FFMPEGReader: Stream couldn't be "
									  "opened.";

AUD_FFMPEGReader::AUD_FFMPEGReader(AUD_Reference<AUD_Buffer> buffer) :
		m_pkgbuf(AVCODEC_MAX_AUDIO_FRAME_SIZE<<1),
		m_membuffer(buffer),
		m_membufferpos(0)
{
	m_membuf = reinterpret_cast<data_t*>(av_malloc(FF_MIN_BUFFER_SIZE + FF_INPUT_BUFFER_PADDING_SIZE));

	m_byteiocontext = av_alloc_put_byte(m_membuf, FF_MIN_BUFFER_SIZE, 0, this,
										read_packet, NULL, seek_packet);

	if(!m_byteiocontext)
	{
		av_free(m_byteiocontext);
		AUD_THROW(AUD_ERROR_FILE, fileopen_error);
	}

	AVProbeData probe_data;
	probe_data.filename = "";
	probe_data.buf = reinterpret_cast<data_t*>(buffer.get()->getBuffer());
	probe_data.buf_size = buffer.get()->getSize();
	AVInputFormat* fmt = av_probe_input_format(&probe_data, 1);

	// open stream
	if(av_open_input_stream(&m_formatCtx, m_byteiocontext, "", fmt, NULL)!=0)
	{
		av_free(m_byteiocontext);
		AUD_THROW(AUD_ERROR_FILE, streamopen_error);
	}

	try
	{
		init();
	}
	catch(AUD_Exception&)
	{
		av_close_input_stream(m_formatCtx);
		av_free(m_byteiocontext);
		throw;
	}
}

AUD_FFMPEGReader::~AUD_FFMPEGReader()
{
	avcodec_close(m_codecCtx);

	if(m_byteiocontext)
	{
		av_close_input_stream(m_formatCtx);
		av_free(m_byteiocontext);
	}
	else
		av_close_input_file(m_formatCtx);
}

int AUD_FFMPEGReader::read_packet(void* opaque, uint8_t* buf, int buf_size)
{
	AUD_FFMPEGReader* reader = reinterpret_cast<AUD_FFMPEGReader*>(opaque);

	int size = AUD_MIN(buf_size, reader->m_membuffer.get()->getSize() - reader->m_membufferpos);

	if(size < 0)
		return -1;

	memcpy(buf, ((data_t*)reader->m_membuffer.get()->getBuffer()) + reader->m_membufferpos, size);
	reader->m_membufferpos += size;

	return size;
}

int64_t AUD_FFMPEGReader::seek_packet(void* opaque, int64_t offset, int whence)
{
	AUD_FFMPEGReader* reader = reinterpret_cast<AUD_FFMPEGReader*>(opaque);

	switch(whence)
	{
	case SEEK_SET:
		reader->m_membufferpos = 0;
		break;
	case SEEK_END:
		reader->m_membufferpos = reader->m_membuffer.get()->getSize();
		break;
	case AVSEEK_SIZE:
		return reader->m_membuffer.get()->getSize();
	}

	return (reader->m_membufferpos += offset);
}

bool AUD_FFMPEGReader::isSeekable() const
{
	return true;
}

void AUD_FFMPEGReader::seek(int position)
{
	if(position >= 0)
	{
		uint64_t st_time = m_formatCtx->start_time;
		uint64_t seek_pos = ((uint64_t)position) * ((uint64_t)AV_TIME_BASE) / ((uint64_t)m_specs.rate);

		if (seek_pos < 0) {
			seek_pos = 0;
		}

		if (st_time != AV_NOPTS_VALUE) {
			seek_pos += st_time;
		}

		double pts_time_base = 
			av_q2d(m_formatCtx->streams[m_stream]->time_base);
		uint64_t pts_st_time =
			((st_time != AV_NOPTS_VALUE) ? st_time : 0)
			/ pts_time_base / (uint64_t) AV_TIME_BASE;

		// a value < 0 tells us that seeking failed
		if(av_seek_frame(m_formatCtx, -1, seek_pos,
				 AVSEEK_FLAG_BACKWARD | AVSEEK_FLAG_ANY) >= 0)
		{
			avcodec_flush_buffers(m_codecCtx);
			m_position = position;

			AVPacket packet;
			bool search = true;

			while(search && av_read_frame(m_formatCtx, &packet) >= 0)
			{
				// is it a frame from the audio stream?
				if(packet.stream_index == m_stream)
				{
					// decode the package
					m_pkgbuf_left = decode(&packet, m_pkgbuf);
					search = false;

					// check position
					if(packet.pts != AV_NOPTS_VALUE)
					{
						// calculate real position, and read to frame!
						m_position = (packet.pts - 
							pts_st_time) * pts_time_base * m_specs.rate;

						if(m_position < position)
						{
							// read until we're at the right position
							int length = AUD_DEFAULT_BUFFER_SIZE;
							sample_t* buffer;
							for(int len = position - m_position;
								length == AUD_DEFAULT_BUFFER_SIZE;
								len -= AUD_DEFAULT_BUFFER_SIZE)
							{
								if(len < AUD_DEFAULT_BUFFER_SIZE)
									length = len;
								read(length, buffer);
							}
						}
					}
				}
				av_free_packet(&packet);
			}
		}
		else
		{
			fprintf(stderr, "seeking failed!\n");
			// Seeking failed, do nothing.
		}
	}
}

int AUD_FFMPEGReader::getLength() const
{
	// return approximated remaning size
	return (int)((m_formatCtx->duration * m_codecCtx->sample_rate)
				 / AV_TIME_BASE)-m_position;
}

int AUD_FFMPEGReader::getPosition() const
{
	return m_position;
}

AUD_Specs AUD_FFMPEGReader::getSpecs() const
{
	return m_specs.specs;
}

void AUD_FFMPEGReader::read(int & length, sample_t* & buffer)
{
	// read packages and decode them
	AVPacket packet;
	int data_size = 0;
	int pkgbuf_pos;
	int left = length;
	int sample_size = AUD_DEVICE_SAMPLE_SIZE(m_specs);

	// resize output buffer if necessary
	if(m_buffer.getSize() < length * AUD_SAMPLE_SIZE(m_specs))
		m_buffer.resize(length * AUD_SAMPLE_SIZE(m_specs));

	buffer = m_buffer.getBuffer();
	pkgbuf_pos = m_pkgbuf_left;
	m_pkgbuf_left = 0;

	// there may still be data in the buffer from the last call
	if(pkgbuf_pos > 0)
	{
		data_size = AUD_MIN(pkgbuf_pos, left * sample_size);
		m_convert((data_t*) buffer, (data_t*) m_pkgbuf.getBuffer(),
				  data_size / AUD_FORMAT_SIZE(m_specs.format));
		buffer += data_size / AUD_FORMAT_SIZE(m_specs.format);
		left -= data_size/sample_size;
	}

	// for each frame read as long as there isn't enough data already
	while((left > 0) && (av_read_frame(m_formatCtx, &packet) >= 0))
	{
		// is it a frame from the audio stream?
		if(packet.stream_index == m_stream)
		{
			// decode the package
			pkgbuf_pos = decode(&packet, m_pkgbuf);

			// copy to output buffer
			data_size = AUD_MIN(pkgbuf_pos, left * sample_size);
			m_convert((data_t*) buffer, (data_t*) m_pkgbuf.getBuffer(),
					  data_size / AUD_FORMAT_SIZE(m_specs.format));
			buffer += data_size / AUD_FORMAT_SIZE(m_specs.format);
			left -= data_size/sample_size;
		}
		av_free_packet(&packet);
	}
	// read more data than necessary?
	if(pkgbuf_pos > data_size)
	{
		m_pkgbuf_left = pkgbuf_pos-data_size;
		memmove(m_pkgbuf.getBuffer(),
				((data_t*)m_pkgbuf.getBuffer())+data_size,
				pkgbuf_pos-data_size);
	}

	buffer = m_buffer.getBuffer();

	if(left > 0)
		length -= left;
	m_position += length;
}
