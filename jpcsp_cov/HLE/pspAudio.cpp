using namespace std;

//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include "pspAudio.h"

namespace jpcsp::HLE
{
	using Emulator = jpcsp::Emulator;

	pspAudio::pspChannelInfo::pspChannelInfo(pspAudio *outerInstance) : outerInstance(outerInstance)
	{
		reserved = false;
		allocatedSamples = 0;
		format = 0;
		lvol = 0x8000;
		rvol = 0x8000;
		outputDataLine = nullptr;
	}

pspAudio *pspAudio::instance;

	pspAudio *pspAudio::get_instance()
	{
		if (instance == nullptr)
		{
			instance = new pspAudio();
		}
		return instance;
	}

	pspAudio::pspAudio()
	{
		pspchannels = new pspChannelInfo*[8];
		for (int i = 0;i < 8;i++)
		{
			pspchannels[i] = new pspChannelInfo(this);
		}

		sampleRate = 48000;
	}

	void pspAudio::sceAudioSetFrequency(int frequency)
	{
		int ret = -1;
		if (frequency == 44100 || frequency == 48000)
		{
			sampleRate = frequency;
			ret = 0;
		}
		Emulator::getProcessor()->gpr[2] = ret; //just return the first channel
	}

	void pspAudio::sceAudioChReserve(int channel, int samplecount, int format)
	{
		if (true)
		{
			cout << "IGNORED sceAudioChReserve channel= " << channel << " samplecount = " << samplecount << " format = " << format << endl;
			Emulator::getProcessor()->gpr[2] = -1;
		}
		else
		{
			cout << "sceAudioChReserve channel= " << channel << " samplecount = " << samplecount << " format = " << format << endl;

			if (channel != -1) // use specified channel, if available
			{
				if (pspchannels[channel]->reserved)
				{
					channel = -1;
				}
			}
			else // find first free channel
			{
				for (int i = 0;i < 8;i++)
				{
					if (!pspchannels[i]->reserved)
					{
						channel = i;
						break;
					}
				}

			}

			if (channel != -1) // if channel == -1 here, it means we couldn't use any.
			{
				pspchannels[channel]->reserved = true;
				pspchannels[channel]->outputDataLine = nullptr; // delay creation until first use.
				pspchannels[channel]->allocatedSamples = samplecount;
				pspchannels[channel]->format = format;
			}
			Emulator::getProcessor()->gpr[2] = channel;
		}
	}

	void pspAudio::sceAudioChRelease(int channel)
	{
		int ret = -1;
		if (pspchannels[channel]->reserved)
		{
			if (pspchannels[channel]->outputDataLine != nullptr)
			{
				pspchannels[channel]->outputDataLine.stop();
				pspchannels[channel]->outputDataLine->close();
			}
			pspchannels[channel]->outputDataLine = nullptr;
			pspchannels[channel]->reserved = false;
			ret = 0;
		}
		Emulator::getProcessor()->gpr[2] = ret; //just return the first channel
	}

	int pspAudio::doAudioOutput(int channel, int pvoid_buf)
	{
		int ret = -1;

		if (pspchannels[channel]->reserved)
		{
			if (pspchannels[channel]->outputDataLine == nullptr) // if not yet initialized, do it now.
			{
				try
				{
					AudioFormat tempVar(sampleRate, 16, 2, true, false);
					pspchannels[channel]->outputDataLine = AudioSystem::getSourceDataLine(&tempVar);
					sceAudioChangeChannelVolume(channel,pspchannels[channel]->lvol,pspchannels[channel]->rvol);
				}
				catch (const LineUnavailableException &e)
				{
					cout << "Exception trying to create channel output line. Channel " << channel << " will be silent." << endl;
					pspchannels[channel]->outputDataLine = nullptr;
					channel = -1;
				}
			}

			if (pspchannels[channel]->outputDataLine != nullptr) // if we couldn't initialize the audio line, just ignore the audio output.
			{
				int channels = ((pspchannels[channel]->format & 0x10) == 0x10)?1:2;
				int bytespersample = 4; //2*channels;

				int bytes = bytespersample * pspchannels[channel]->allocatedSamples;

				signed char *data = new signed char[bytes];

				/*
				for(int i=0;i<bytes;i++)
				{
				    data[i] = (byte)Emulator.getMemory().read8(pvoid_buf+i);
				}
				 */

				// process audio volumes ourselves for now
				if (channels == 1)
				{
					int nsamples = pspchannels[channel]->allocatedSamples;
					for (int i = 0;i < nsamples;i++)
					{
						short lval = static_cast<short>(Emulator::getMemory()->read16(pvoid_buf + i));
						short rval = lval;

						lval = static_cast<short>(((static_cast<int>(lval)) * pspchannels[channel]->lvol) >> 16);
						rval = static_cast<short>(((static_cast<int>(rval)) * pspchannels[channel]->rvol) >> 16);

						data[i * 4 + 0] = static_cast<signed char>(lval);
						data[i * 4 + 1] = static_cast<signed char>(lval >> 8);
						data[i * 4 + 2] = static_cast<signed char>(rval);
						data[i * 4 + 3] = static_cast<signed char>(rval >> 8);
					}
				}
				else
				{
					int nsamples = pspchannels[channel]->allocatedSamples;
					for (int i = 0;i < nsamples;i++)
					{
						short lval = static_cast<short>(Emulator::getMemory()->read16(pvoid_buf + i * 2));
						short rval = static_cast<short>(Emulator::getMemory()->read16(pvoid_buf + i * 2 + 1));

						lval = static_cast<short>(((static_cast<int>(lval)) * pspchannels[channel]->lvol) >> 16);
						rval = static_cast<short>(((static_cast<int>(rval)) * pspchannels[channel]->rvol) >> 16);

						data[i * 4 + 0] = static_cast<signed char>(lval);
						data[i * 4 + 1] = static_cast<signed char>(lval >> 8);
						data[i * 4 + 2] = static_cast<signed char>(rval);
						data[i * 4 + 3] = static_cast<signed char>(rval >> 8);
					}
				}

				pspchannels[channel]->outputDataLine.write(data,0,data->length);
				pspchannels[channel]->outputDataLine.start();

				ret = 0;
			}
		}

		return ret; //just return the first channel
	}

	int pspAudio::doAudioFlush(int channel)
	{
		if (pspchannels[channel]->outputDataLine != nullptr)
		{

//====================================================================================================
//End of the allowed output for the Free Edition of Java to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================
