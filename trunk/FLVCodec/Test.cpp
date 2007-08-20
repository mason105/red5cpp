// FLVEncoder.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <conio.h>
#include "GrapObjRef.h"
#include <process.h>

bool bc = true;
static void  cb(void *p)
{
	CGrapObjRef* p_sys = (CGrapObjRef*)p;
	CDShowStream *p_stream = NULL;
	XMPMediaSample sample;
	int i_data_size, i_stream;
	BYTE *p_data;
	while (bc) 
	{
		LONGLONG llDur = 0;
		HRESULT hr = p_sys->GetCurrentPosition(&llDur);

		for( i_stream = 0; i_stream < p_sys->get_streamcount(); i_stream++ )
		{
			p_stream = p_sys->get_stream(i_stream);
			if( p_stream->mt.majortype == MEDIATYPE_Audio &&
				p_stream->p_capture_filter &&
				p_stream->p_capture_filter->CustomGetPin()
				->CustomGetSample( &sample ) == S_OK )
			{
				break;
			}
		}
		if( i_stream == p_sys->get_streamcount() )
		{
			for( i_stream = 0; i_stream < p_sys->get_streamcount(); i_stream++ )
			{
				p_stream = p_sys->get_stream(i_stream);
				if( p_stream->p_capture_filter &&
					p_stream->p_capture_filter->CustomGetPin()
					->CustomGetSample( &sample ) == S_OK )
				{
					break;
				}
			}
		}

		if( i_stream == p_sys->get_streamcount() )
		{
			Sleep( 100 );
			continue;
		}

		i_data_size = sample.p_sample->GetActualDataLength();
		sample.p_sample->GetPointer( &p_data );

		REFERENCE_TIME i_pts, i_end_date;
		hr = sample.p_sample->GetTime( &i_pts, &i_end_date );
		if( hr != VFW_S_NO_STOP_TIME && hr != S_OK ) i_pts = 0;

		if( !i_pts )
		{
			if( p_stream->mt.majortype == MEDIATYPE_Video || !p_stream->b_pts )
			{
				/* Use our data timestamp */
				i_pts = sample.i_timestamp;
				p_stream->b_pts = true;
			}
		}

		i_pts /= 10;

		sample.p_sample->Release();

		printf("get sample:     %d          %d        %I64d\n", i_stream, i_data_size, i_pts);
	}
	return ;
}
int main(int argc, char* argv[])
{
	CoInitialize(NULL);
	char szParam[2048] = "\0";

	list<string> list_vdev;
	list<string> list_adev;
	list<string> list_vdisplay;
	list<string> list_adisplay;

	CBaseGrapBuilder::FindCaptureDevice(NULL, NULL, &list_vdev, &list_vdisplay, false);
	CBaseGrapBuilder::FindEncoderDevice(NULL, NULL, &list_vdev, &list_vdisplay);
	CBaseGrapBuilder::FindCaptureDevice(NULL, NULL, &list_adev, &list_adisplay, true);
	CGrapObjRef* fgb = new CGrapObjRef;

	long nDeviceNum = 3;
	long nCount		= 0;
loop:
	list<string>::iterator it_adev;
	list<string>::iterator it_adisplay;
	long	nDeviceIndex = 0;
	it_adev = list_adev.begin();
	it_adisplay = list_adisplay.begin();
	for(; it_adev != list_adev.end(); it_adev++, it_adisplay++)
	{
		//if(strnicmp((*it_adev).c_str(), "Gotron MP-4X V3 Audio",
		//	strlen("Gotron MP-4X V3 Audio")) == 0)
		if(strnicmp((*it_adev).c_str(), "Conexant HD Audio input",
			strlen("Conexant HD Audio input")) == 0)
			break;
			//		if(strnicmp((*it_adev).c_str(), "GOTRON MP-400 Analog Audio Capture",
			//			strlen("GOTRON MP-400 Analog Audio Capture")) == 0)
		{
		//	if(nDeviceIndex == 0)
		//		break;
		//	nDeviceIndex++;
		}
	}
	list<string>::iterator it_vdev;
	list<string>::iterator it_vdisplay;
	nDeviceIndex = 0;
	it_vdev = list_vdev.begin();
	it_vdisplay = list_vdisplay.begin();
	for(; it_vdev != list_vdev.end(); it_vdev++, it_vdisplay++)
	{
		//if(strnicmp((*it_vdev).c_str(), "Gotron MP-4X V3 Video",
		//	strlen("Gotron MP-4X V3 Video")) == 0)
		if(strnicmp((*it_vdev).c_str(), "Logitech QuickCam Communicate STX",
			strlen("Logitech QuickCam Communicate STX")) == 0)
			break;
			//		if(strnicmp((*it_vdev).c_str(), "GOTRON MP-400 Capture",
			//			strlen("GOTRON MP-400 Capture")) == 0)
			//		if(strnicmp((*it_vdev).c_str(), "Gotron GoDVB ASI TS Capture",
			//			strlen("Gotron GoDVB ASI TS Capture")) == 0)
		{
		//	if(nDeviceIndex == nCount)
		//		break;
		//	nDeviceIndex++;
		}
	}
	printf("%s,%s,%s,%s\n",
	(*it_vdev).c_str(),
		(*it_adev).c_str(),
		(*it_vdisplay).c_str(),
		(*it_adisplay).c_str());

	//	sprintf(szParam, "%s", "D:\\1.mpg");
	sprintf(szParam, "dshow-vdev=%s;dshow-adev=%s;dshow-vdev-display=%s;\
					 dshow-adev-display=%s;Width=%d;\
					 Height=%d;dshow-chroma=%d;\
					 dshow-fps=%f;dshow-audio-channel=%d;\
					 dshow-audio-samplespersec=%d;\
					 dshow-audio-bitspersample=%d;dshow-config=%d;\
					 dshow-tuner=%d;dshow-PhysConnType=%d;\
					 dshow-AnalogVideoStandard=%d;\
					 dshow-vcodec=%d;dshow-acodec=%d;\
					 dshow-vb=%d;dshow-ab=%d;", 
					 (*it_vdev).c_str(),
					 (*it_adev).c_str(),
					 (*it_vdisplay).c_str(),
					 (*it_adisplay).c_str(),
					 352,
					 288,
					 0,
					 15.0,
					 1,
					 22050,
					 16,
					 false,
					 false,
					 3,
					 0x20,
					 0,
					 0,
					 1024,
					 128);
	if(FAILED(fgb->Initialize(szParam, GrapBuilderType_FLV)))
	{
	printf("Initialize failed\n");
	_getch();
	goto errexit;
	}
	/*sprintf(szParam, "D:\\Code Develpment\\GrapTest\\deviceconfig.xml");
	if(FAILED(fgb->InitializeFromConfig(szParam)))
	{
		printf("Initialize failed\n");
		goto errexit;
	}*/
	//if( ++ nCount < nDeviceNum)
	//	goto loop;
	OutputDebugString("run before\n");
	fgb->ShowFilterSettings(0, FilterSettingType_Encode, false);
	fgb->ShowFilterSettings(0, FilterSettingType_Encode, true);

	if(FAILED(fgb->Run()))
	{
		printf("run failed\n");
		_getch();
	goto errexit;
	}
	//fgb->Stop();
	OutputDebugString("run after\n");

	_beginthread(cb, 0, fgb);
	_getch();
	bc = false;
	Sleep(1000);
errexit:
	fgb->Stop();

	fgb->Cleanup();

	delete fgb;
	return 0;
}

