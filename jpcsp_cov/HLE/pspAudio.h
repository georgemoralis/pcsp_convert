#pragma once

#include "../Emulator.h"
#include <iostream>
#include "exceptionhelper.h"

/*
Function:
- HLE everything in http://psp.jim.sh/pspsdk-doc/group__Audio.html


This file is part of jpcsp.

Jpcsp is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Jpcsp is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Jpcsp.  If not, see <http://www.gnu.org/licenses/>.
 */
namespace jpcsp::HLE
{


	/**
	 *
	 * @author shadow
	 */
	class pspAudio
	{

	private:
		class pspChannelInfo
		{
		private:
			pspAudio *outerInstance;


		public:
			bool reserved = false;
			int allocatedSamples = 0;
			int format = 0;
			int lvol = 0;
			int rvol = 0;
			SourceDataLine *outputDataLine;

			virtual ~pspChannelInfo()
			{
				delete outputDataLine;
				delete outerInstance;
			}

			pspChannelInfo(pspAudio *outerInstance);
		};

	private:
		pspChannelInfo **pspchannels; // psp channels
		int sampleRate = 0;

		static pspAudio *instance;

	public:
		virtual ~pspAudio()
		{
			delete[] pspchannels;
		}

		static pspAudio *get_instance();
		pspAudio();

		const int PSP_AUDIO_VOLUME_MAX = 0x8000;
		const int PSP_AUDIO_CHANNEL_MAX = 8;
		const int PSP_AUDIO_NEXT_CHANNEL = (-1);
		const int PSP_AUDIO_SAMPLE_MIN = 64;
		const int PSP_AUDIO_SAMPLE_MAX = 65472;

		const int PSP_AUDIO_FORMAT_STEREO = 0;
		const int PSP_AUDIO_FORMAT_MONO = 0x10;

		const int PSP_AUDIO_FREQ_44K = 44100;
		const int PSP_AUDIO_FREQ_48K = 48000;

		virtual void sceAudioSetFrequency(int frequency);

		//Allocate and initialize a hardware output channel.
		virtual void sceAudioChReserve(int channel, int samplecount, int format);

		//Release a hardware output channel.
		virtual void sceAudioChRelease(int channel);

	private:
		int doAudioOutput(int channel, int pvoid_buf);

		int doAudioFlush(int channel);

		//Output audio of the specified channel.
	public:
		virtual void sceAudioOutput(int channel, int vol, int pvoid_buf);

		//Output audio of the specified channel (blocking).
		virtual void sceAudioOutputBlocking(int channel, int vol, int pvoid_buf);

		//Output panned audio of the specified channel.
		virtual void sceAudioOutputPanned(int channel, int leftvol, int rightvol, int pvoid_buf);

		//Output panned audio of the specified channel (blocking).
		virtual void sceAudioOutputPannedBlocking(int channel, int leftvol, int rightvol, int pvoid_buf);

		//Get count of unplayed samples remaining.
		virtual void sceAudioGetChannelRestLen(int channel);

		//Change the output sample count, after it's already been reserved.
		virtual void sceAudioSetChannelDataLen(int channel, int samplecount);

		//Change the format of a channel.
		virtual void sceAudioChangeChannelConfig(int channel, int format);

		//Change the volume of a channel.
		virtual void sceAudioChangeChannelVolume(int channel, int leftvol, int rightvol);

		////////////////////////////////////////////////////////////////////////////
		// Functions after this point are not yet implemented.

		//Reserve the audio output and set the output sample count.
		virtual void sceAudioOutput2Reserve(int samplecount);
		//Release the audio output.
		virtual void sceAudioOutput2Release();
		//Change the output sample count, after it's already been reserved.
		virtual void sceAudioOutput2ChangeLength(int samplecount);
		//Output audio (blocking).
		virtual void sceAudioOutput2OutputBlocking(int vol, int pvoid_buf);
		//Get count of unplayed samples remaining.
		virtual void sceAudioOutput2GetRestSample();
		//Reserve the audio output.
		virtual void sceAudioSRCChReserve(int samplecount, int freq, int channels);
		//Release the audio output.
		virtual void sceAudioSRCChRelease();
		//Output audio.
		virtual void sceAudioSRCOutputBlocking(int vol, int pvoid_buf);
		//Init audio input.
		virtual void sceAudioInputInit(int unknown1, int gain, int unknown2);
		//Init audio input (with extra arguments).
		virtual void sceAudioInputInitEx(int p_pspAudioInputParams_params);
		//Perform audio input (blocking).
		virtual void sceAudioInputBlocking(int samplecount, int freq, int pvoid_buf);
		//Perform audio input.
		virtual void sceAudioInput(int samplecount, int freq, int pvoid_buf);
		//Get the number of samples that were acquired.
		virtual void sceAudioGetInputLength();
		//Wait for non-blocking audio input to complete.
		virtual void sceAudioWaitInputEnd();
		//Poll for non-blocking audio input status.
		virtual void sceAudioPollInputEnd();

	};

}
