/******************************************************************************
*
*    Copyright WIS Technologies (c) (2003)
*    All Rights Reserved
*
*******************************************************************************
*
*    FILE: 
*        config_text_parser.h
*
*    DESCRIPTION:
*        
*   
*
*    AUTHOR:
*	
*
*    <SOURCE CONTROL TAGS TBD>
*
******************************************************************************/

#ifndef __CONFIG_TEXT_PARSER_H__
#define __CONFIG_TEXT_PARSER_H__

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_LINE	1000
#define MAX_SYMBOL	1000

struct CONFIG_FILE_HEADER
{
	UINT32 _file_version;					// identification
	UINT32 _file_length;					// exclude header length
//	UINT32 _num_of_stream_configs;			// stream configuration count
//	UINT32 _num_of_resolution_configs;		// resolution configuration count
//	UINT32 _num_of_bitrate_configs;			// bitrate control configuration count
//	UINT32 _num_of_association;				// number of associations
};

struct SYMBOL
{
	char*						_name;
	enum ASSOCIATION_TYPE		_type;
	long						_index;
};

typedef struct _PARSE_HANDLE_
{
	FILE*				_fp;

	enum CONFIG_ERROR	_last_error;
	char				_error_context[MAX_LINE];
	UINT32				_line_number;
	SINT8				_line_current[MAX_LINE];

	UINT32				_num_of_symbols;
	struct SYMBOL		_symbols[MAX_SYMBOL];

	struct CONFIG_FILE_HEADER	_header;
	_VIDEO_CAPABILITIES*		_video_caps;
	_VIDEO_PROFILES				_video_profiles;
} _PARSE_HANDLE, * PARSE_HANDLE;

PARSE_HANDLE OpenConfigurationFile(const char* szFilePath);
void CloseConfigurationFile(PARSE_HANDLE handle);
enum CONFIG_ERROR ParseConfigurationFile(PARSE_HANDLE handle, _VIDEO_CAPABILITIES* caps, _VIDEO_PROFILES* profiles);
enum CONFIG_ERROR GetParseErrorInformation(PARSE_HANDLE handle, UINT32* line);

#ifdef __cplusplus
}
#endif


#endif

/*************************** end of config_text_parser.h *********************/
