/******************************************************************************
*
*    Copyright WIS Technologies (c) (2003)
*    All Rights Reserved
*
*******************************************************************************
*
*    FILE: 
*        config_text_parser.c
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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "stdafx.h"
#include "typedef.h"
#include "struct.h"
#include "config_error.h"
#include "config_helper.h"
#include "config_text_parser.h"
#include <io.h>
#include <stdlib.h>

static _PARSE_HANDLE __gHandle;

enum LINE_TYPE
{
	LINE_BLANK,					// blank line or comments
	LINE_STREAM_SECTION,		// start line of stream setting section
	LINE_FRAMERATE_SECTION,		// start line of frame rate setting section
	LINE_RESOLUTION_SECTION,	// start line of resolution setting section
	LINE_BITRATE_SECTION,		// start line of bitrate setting section
	LINE_NAME_VALUE_PAIR,
	LINE_ERROR,
	LINE_END
};

void TrimBlankCharacters(char* string)	// remove all the blank characters except those in the double quotes
{
	UINT32 inside_quote = 0;
	UINT32 length = strlen(string);
	UINT32 i, j;

	for (  i = 0 , j = 0 ; i < length ; i ++ )
	{
		switch ( string[i] )
		{
			case '"':
				inside_quote = 1 - inside_quote;

			case '\n':
			case '\r':
				break;
			case ' ':
			case '\t':
				if ( inside_quote == 0 ) break;
				// fall through
			default:
				if ( i != j ) string[j] = string[i];
				j ++;
				break;
		}
	}
	string[j] = 0;
}

void TrimComments(char* string) // trim all comments
{
	UINT32 inside_quote = 0;
	UINT32 backslash_count = 0;
	UINT32 length = strlen(string);
	UINT32 i;

	for (  i = 0 ; i < length ; i ++ )
	{
		switch ( string[i] )
		{
			case '/':
				if ( inside_quote == 0 ) backslash_count ++;
				if ( backslash_count == 2 )
				{
					string[i-1] = 0;
					return;
				}
				break;				
			case '"':
				inside_quote = 1 - inside_quote;
				break;
			default:
				backslash_count = 0;
				break;
		}
	}
}

enum LINE_TYPE ParseLine(PARSE_HANDLE handle, char** name, char** value)
{
	char* __name = NULL;
	char* __value = NULL;
	char* line = handle->_line_current;
	UINT32 length = 0;

	if ( fgets(line, MAX_LINE, handle->_fp) == NULL ) 
		return LINE_END;
	
	handle->_line_number ++;

	TrimComments(line);
	TrimBlankCharacters(line);

	length = strlen(line);
	if ( length == 0 ) return LINE_BLANK;

	if ( line[0] == '[' ) // section begin
	{
		strlwr(line);
		if ( strcmp(line, "[streamsetting]") == 0 )
			return LINE_STREAM_SECTION;		// start line of stream setting section
		else if ( strcmp(line, "[frameratesetting]") == 0 )
			return LINE_FRAMERATE_SECTION;	// start line of framerate setting section
		else if ( strcmp(line, "[resolutionsetting]") == 0 )
			return LINE_RESOLUTION_SECTION;	// start line of resolution setting section
		else if ( strcmp(line, "[bitratesetting]") == 0 )
			return LINE_BITRATE_SECTION;	// start line of bitrate setting section
		else 
			return LINE_ERROR;
	}
	else 
	{
		__name = line;
		__value = strchr(line, '=');
		if ( __value == NULL ) return LINE_ERROR;

		__value[0] = 0;
		if ( name != NULL )	*name = __name;
		if ( value != NULL ) *value = __value + 1;
		return LINE_NAME_VALUE_PAIR;
	}
	
	return LINE_ERROR;
}

void DumpAssociations(PARSE_HANDLE handle)
{
/*	unsigned long i;

	for ( i = 0 ; i < handle->_video_caps->_num_of_associations ; i ++ )
	{
		TCFGASSOCIATION* assoc = handle->_video_caps->_associations + i;
		char szContent[1000];
		char *szMasterName, *szSlaveName;
		switch ( assoc->_master_type )
		{
			case TYPE_SYSTEM_CONFIG:
				szMasterName = ( assoc->_master_id == ASSOCIATION_ALL ) ?
							"all system setting"
							: handle->_video_caps->_system_configs[assoc->_master_id].header.name;
				break;
			case TYPE_STREAM_CONFIG:
				szMasterName = ( assoc->_master_id == ASSOCIATION_ALL ) ?
							"all stream setting"
							: handle->_video_caps->_stream_configs[assoc->_master_id].header.name;
				break;
			case TYPE_RESOLUTION_CONFIG:
				szMasterName = ( assoc->_master_id == ASSOCIATION_ALL ) ?
							"all resolution setting"
							: handle->_video_caps->_resolution_configs[assoc->_master_id].header.name;
				break;
			case TYPE_BITRATE_CONFIG:
				szMasterName = ( assoc->_master_id == ASSOCIATION_ALL ) ?
							"all bitrate setting"
							: handle->_video_caps->_bitrate_configs[assoc->_master_id].header.name;
				break;
			case TYPE_FRAMERATE_CONFIG:
				szMasterName = ( assoc->_master_id == ASSOCIATION_ALL ) ?
							"all framerate setting"
							: handle->_video_caps->_framerate_configs[assoc->_master_id].header.name;
				break;
		}
		switch ( assoc->_slave_type )
		{
			case TYPE_SYSTEM_CONFIG:
				szSlaveName = ( assoc->_slave_id == ASSOCIATION_ALL ) ?
							"all system setting"
							: handle->_video_caps->_system_configs[assoc->_slave_id].header.name;
				break;
			case TYPE_STREAM_CONFIG:
				szSlaveName = ( assoc->_slave_id == ASSOCIATION_ALL ) ?
							"all stream setting"
							: handle->_video_caps->_stream_configs[assoc->_slave_id].header.name;
				break;
			case TYPE_RESOLUTION_CONFIG:
				szSlaveName = ( assoc->_slave_id == ASSOCIATION_ALL ) ?
							"all resolution setting"
							: handle->_video_caps->_resolution_configs[assoc->_slave_id].header.name;
				break;
			case TYPE_BITRATE_CONFIG:
				szSlaveName = ( assoc->_slave_id == ASSOCIATION_ALL ) ?
							"all bitrate setting"
							: handle->_video_caps->_bitrate_configs[assoc->_slave_id].header.name;
				break;
			case TYPE_FRAMERATE_CONFIG:
				szSlaveName = ( assoc->_slave_id == ASSOCIATION_ALL ) ?
							"all framerate setting"
							: handle->_video_caps->_framerate_configs[assoc->_slave_id].header.name;
				break;
		}
		sprintf(szContent, " %s - %s : %s", szMasterName, szSlaveName, assoc->_associate_type == ASSOCIATION_TYPE_ALLOW ? "allow" : "deny");
		OutputDebugString(szContent);
	}
*/
}

long AddAssociation(PARSE_HANDLE handle, TCFGASSOCIATION* assoc)
{
	if ( handle->_video_caps->_num_of_associations >= MAX_ASSOCIATION ) return -3;

	handle->_video_caps->_associations[handle->_video_caps->_num_of_associations] = *assoc;

	return ++ handle->_video_caps->_num_of_associations;
}

long AddSymbol(PARSE_HANDLE handle, char* name, enum ASSOCIATION_TYPE type, long index)
{
/*	unsigned long i;

	if ( handle->_num_of_symbols >= MAX_SYMBOL ) return -3;

	for ( i = 0 ; i < handle->_num_of_symbols ; i ++ )
	{
		if ( strcmp(handle->_symbols[i]._name, name) == 0 && handle->_symbols[i]._type == type )
		{
			/////////////////////////////////////////////////////////
			// find a matched entry
			/////////////////////////////////////////////////////////
			if ( handle->_symbols[i]._index >= 0 && index >= 0 && handle->_symbols[i]._index != (unsigned long)(index) ) // different index are specified
				return -3;
			if ( handle->_symbols[i]._index < 0 && index >= 0 ) handle->_symbols[i]._index = (unsigned long)(index);	// save the index
			return i;	
		}
	}

	handle->_symbols[handle->_num_of_symbols]._name = strdup(name);
	handle->_symbols[handle->_num_of_symbols]._index = index;
	handle->_symbols[handle->_num_of_symbols]._type = type;

	handle->_num_of_symbols ++;
	return handle->_num_of_symbols - 1;
*/
	return 1;
}

enum CONFIG_ERROR ResolveSymbols(PARSE_HANDLE handle)
{
/*	unsigned long i;

	for ( i = 0 ; i < handle->_video_caps->_num_of_associations ; i ++ )
	{
		TCFGASSOCIATION* assoc = handle->_video_caps->_associations + i;

		if ( assoc->_master_id != ASSOCIATION_ALL )
		{
			if ( assoc->_master_type != handle->_symbols[assoc->_master_id]._type ) return ERROR_UNKNOWN;
			strcpy(handle->_error_context, handle->_symbols[assoc->_master_id]._name);
			if ( handle->_symbols[assoc->_master_id]._index < 0 ) return ERROR_PARSER_INVALID_SYMBOL;
			assoc->_master_id = handle->_symbols[assoc->_master_id]._index;
		}

		if ( assoc->_slave_id != ASSOCIATION_ALL )
		{
			if ( assoc->_slave_type != handle->_symbols[assoc->_slave_id]._type ) return ERROR_UNKNOWN;
			strcpy(handle->_error_context, handle->_symbols[assoc->_slave_id]._name);
			if (  handle->_symbols[assoc->_slave_id]._index < 0 ) return ERROR_PARSER_INVALID_SYMBOL;
			assoc->_slave_id = handle->_symbols[assoc->_slave_id]._index;
		}
	}
*/
	return ERROR_NONE;
}

enum CONFIG_ERROR CheckStreamConfig(PARSE_HANDLE handle, TCFGSTREAM* stream)
{
	unsigned long i;

	/////////////////////////////////////////
	// check name
	/////////////////////////////////////////
	if ( (stream->header.flags & FLAGS_NAME) == 0 || strlen(stream->header.name) == 0 )
		return ERROR_PARSER_INVALID_ENTRY_NAME;

	for ( i = 0 ; i < handle->_video_profiles._num_of_stream_profiles ; i ++ )
	{
		if ( strcmp(stream->header.name, handle->_video_profiles._stream_profiles[i].header.name) == 0 )
			return ERROR_PARSER_DUPLICATED_ENTRY_NAME;
	}

	/////////////////////////////////////////
	// check compress mode
	/////////////////////////////////////////
	if ( (stream->header.flags & FLAGS_STREAM_COMPRESS_MODE) == 0 )
		return ERROR_PARSER_STREAM_PARAMETER_MISSING;

	if ( stream->compress_mode != MPEG1 && stream->compress_mode != MPEG2
		&& stream->compress_mode != MPEG4 && stream->compress_mode != MOTIONJPEG
		&& stream->compress_mode != H263 && stream->compress_mode != MPEG1 + GO
		&& stream->compress_mode != MPEG2 + GO && stream->compress_mode != MPEG4 + GO
		&& stream->compress_mode != H263 + GO )
		return ERROR_PARSER_INVALID_COMPRESS_MODE;
		
	/////////////////////////////////////////
	// check sequence mode
	/////////////////////////////////////////
	if ( ( stream->header.flags & FLAGS_STREAM_COMPRESS_MODE ) == 0 )
		return ERROR_PARSER_STREAM_PARAMETER_MISSING;

	if ( stream->sequence != IONLY && stream->sequence != IPONLY && stream->sequence != IPB )
		return ERROR_PARSER_INVALID_SEQUENCE_MODE;

	/////////////////////////////////////////
	// check gop mode
	/////////////////////////////////////////
	if ( (stream->header.flags & FLAGS_STREAM_GOP_MODE) == 0 )
		stream->gop_mode = 0;

	if ( stream->gop_mode != 0 ) stream->gop_mode = 1;

	/////////////////////////////////////////
	// check gop size
	/////////////////////////////////////////
	if ( (stream->header.flags & FLAGS_STREAM_GOP_SIZE) == 0 )
		stream->gop_size = 0;	// nothing to check

	/////////////////////////////////////////
	// check mpeg4 mode
	/////////////////////////////////////////
	if ( (stream->header.flags & FLAGS_STREAM_MPEG4_MODE) == 0 )
	{
		if ( stream->compress_mode == MPEG4 || stream->compress_mode == MPEG4 + GO )
			return ERROR_PARSER_INVALID_MPEG4_MODE;
		stream->mpeg4_mode = 0;
	}
	else 
	{
		if ( stream->mpeg4_mode < MIN_MPEG4_MODE || stream->mpeg4_mode > MAX_MPEG4_MODE )
			return ERROR_PARSER_INVALID_MPEG4_MODE;
	}

	/////////////////////////////////////////
	// check dvd compliant
	/////////////////////////////////////////
	if ( (stream->header.flags & FLAGS_STREAM_DVD_COMPLIANT) == 0 )	stream->DVD_compliant = 0;
	if ( stream->DVD_compliant != 0 ) stream->DVD_compliant = 1;

	/////////////////////////////////////////
	// check deinterlace mode
	/////////////////////////////////////////
	if ( (stream->header.flags & FLAGS_STREAM_DEINTERLACE_MODE) != 0 )
	{
		if ( stream->deinterlace_mode == 2 && stream->compress_mode != MPEG2 )
			return ERROR_PARSER_INVALID_DEINTERLACE_MODE;

		if ( stream->deinterlace_mode > 2 || stream->deinterlace_mode < 0 )
			return ERROR_PARSER_INVALID_DEINTERLACE_MODE;
	}

	/////////////////////////////////////////
	// check search range
	/////////////////////////////////////////
	if ( (stream->header.flags & FLAGS_STREAM_SEARCH_RANGE) != 0 )
	{
		if ( stream->search_range != 16 && stream->search_range != 32
			&& stream->search_range != 64 && stream->search_range != 128 )
			return ERROR_PARSER_INVALID_SEARCH_RANGE;
	}

	/////////////////////////////////////////
	// check mpeg headers
	/////////////////////////////////////////
	if ( (stream->header.flags & FLAGS_STREAM_GOPHEAD_ENABLE) != 0 )
		if ( stream->gop_head_enable != 0 ) stream->gop_head_enable = 1;

	if ( (stream->header.flags & FLAGS_STREAM_SEQHEAD_ENABLE) != 0 )
		if ( stream->seq_head_enable != 0 ) stream->seq_head_enable = 1;

	/////////////////////////////////////////
	// aspect ratio
	/////////////////////////////////////////
	if ( (stream->header.flags & FLAGS_STREAM_ASPECT_RATIO) != 0 )
	{
		if ( stream->aspect_ratio < 1 || stream->aspect_ratio > 3 )
			return ERROR_PARSER_INVALID_ASPECT_RATIO;
	}

	return ERROR_NONE;
}

enum CONFIG_ERROR ParseStreamConfig(PARSE_HANDLE handle, enum LINE_TYPE* line)
{
	char * __name;
	char * __value;
	TCFGSTREAM* stream;
	enum CONFIG_ERROR error;
	long stream_cap_index;
	long stream_symbol_index;
	long total_res_association = 0;
	long total_fps_association = 0;
	long total_brc_association = 0;

	if ( handle->_video_profiles._num_of_stream_profiles >= MAX_STREAM_CONFIG ) 
		return ERROR_PARSER_TOO_MUCH_CONFIG;

	stream = &(handle->_video_profiles._stream_profiles[handle->_video_profiles._num_of_stream_profiles]);

	for ( ; ; )
	{
		*line = ParseLine(handle, &__name, &__value);
		if ( *line == LINE_BLANK ) continue;
		if ( *line != LINE_NAME_VALUE_PAIR ) break;

		if ( strcmp(__name, "name") == 0 )
		{
			stream->header.flags |= FLAGS_NAME;
			strcpy(stream->header.name, __value);

			stream_symbol_index = AddSymbol(handle, 
									stream->header.name, 
									TYPE_STREAM_CONFIG, 
									handle->_video_profiles._num_of_stream_profiles);

			if ( stream_symbol_index < 0 ) return ERROR_CONFIG_TOO_MUCH_ENTRY;
			strcpy(handle->_error_context, __value);
		}
		else if ( strcmp(__name, "desc") == 0 )
		{
			stream->header.flags |= FLAGS_DESC;
			strcpy(stream->header.desc, __value);
		}
		else if ( strcmp(__name, "compress_mode") == 0 )
		{
			stream->header.flags |= FLAGS_STREAM_COMPRESS_MODE;
			stream->compress_mode = (EVideoFormat)atoi(__value);
		}
		else if ( strcmp(__name, "sequence") == 0 )
		{
			stream->header.flags |= FLAGS_STREAM_SEQUENCE_MODE;
			stream->sequence = (ESequenceMode )atoi(__value);
		}
		else if ( strcmp(__name, "gop_mode") == 0 )
		{
			stream->header.flags |= FLAGS_STREAM_GOP_MODE;
			stream->gop_mode = atoi(__value);
		}
		else if ( strcmp(__name, "gop_size") == 0 )
		{
			stream->header.flags |= FLAGS_STREAM_GOP_SIZE;
			stream->gop_size = atoi(__value);
		}
		else if ( strcmp(__name, "mpeg4_mode") == 0 )
		{
			stream->header.flags |= FLAGS_STREAM_MPEG4_MODE;
			stream->mpeg4_mode = atoi(__value);
		}
		else if ( strcmp(__name, "DVD_compliant") == 0 )
		{
			stream->header.flags |= FLAGS_STREAM_DVD_COMPLIANT;
			stream->DVD_compliant = atoi(__value);
		}
		else if ( strcmp(__name, "deinterlace_mode") == 0 )
		{
			stream->header.flags |= FLAGS_STREAM_DEINTERLACE_MODE;
			stream->deinterlace_mode = atoi(__value);
		}
		else if ( strcmp(__name, "search_range") == 0 )
		{
			stream->header.flags |= FLAGS_STREAM_SEARCH_RANGE;
			stream->search_range = atoi(__value);
		}
		else if ( strcmp(__name, "gop_head_enable") == 0 )
		{
			stream->header.flags |= FLAGS_STREAM_GOPHEAD_ENABLE;
			stream->gop_head_enable = atoi(__value);
		}
		else if ( strcmp(__name, "seq_head_enable") == 0 )
		{
			stream->header.flags |= FLAGS_STREAM_SEQHEAD_ENABLE;
			stream->seq_head_enable = atoi(__value);
		}
		else if ( strcmp(__name, "aspect_ratio") == 0 )
		{
			stream->header.flags |= FLAGS_STREAM_ASPECT_RATIO;
			stream->aspect_ratio = atoi(__value);
		}
		else if ( strcmp(__name, "rescfg") == 0 )
		{
			TCFGASSOCIATION assoc;
			long res_index = AddSymbol(handle, 
									__value, 
									TYPE_RESOLUTION_CONFIG, 
									-1);	// resolved later
			if ( res_index < 0 ) return ERROR_CONFIG_TOO_MUCH_ENTRY;
			assoc._master_type = TYPE_STREAM_CONFIG;
			assoc._master_id = stream_symbol_index;
			assoc._slave_type = TYPE_RESOLUTION_CONFIG;
			assoc._slave_id = res_index;
			assoc._associate_type = ASSOCIATION_TYPE_ALLOW;
			if ( AddAssociation(handle, &assoc) < 0 ) return ERROR_CONFIG_TOO_MUCH_ENTRY;
			total_res_association ++;
		}
		else if ( strcmp(__name, "fpscfg") == 0 )
		{
			TCFGASSOCIATION assoc;
			long fps_index = AddSymbol(handle, 
									__value, 
									TYPE_FRAMERATE_CONFIG, 
									-1);	// resolved later
			if ( fps_index < 0 ) return ERROR_CONFIG_TOO_MUCH_ENTRY;
			assoc._master_type = TYPE_STREAM_CONFIG;
			assoc._master_id = stream_symbol_index;
			assoc._slave_type = TYPE_FRAMERATE_CONFIG;
			assoc._slave_id = fps_index;
			assoc._associate_type = ASSOCIATION_TYPE_ALLOW;
			if ( AddAssociation(handle, &assoc) < 0 ) return ERROR_CONFIG_TOO_MUCH_ENTRY;
			total_fps_association ++;
		}
		else if ( strcmp(__name, "ctlcfg") == 0 )
		{
			TCFGASSOCIATION assoc;
			long brc_index = AddSymbol(handle, 
									__value, 
									TYPE_BITRATE_CONFIG, 
									-1);	// resolved later
			if ( brc_index < 0 ) return ERROR_CONFIG_TOO_MUCH_ENTRY;
			assoc._master_type = TYPE_STREAM_CONFIG;
			assoc._master_id = stream_symbol_index;
			assoc._slave_type = TYPE_BITRATE_CONFIG;
			assoc._slave_id = brc_index;
			assoc._associate_type = ASSOCIATION_TYPE_ALLOW;
			if ( AddAssociation(handle, &assoc) < 0 ) return ERROR_CONFIG_TOO_MUCH_ENTRY;
			total_brc_association ++;
		}
		else
		{
			return ERROR_UNKNOWN_STREAM_PARAMETER;
		}
	}

	if ( total_res_association > 0 )
	{
		TCFGASSOCIATION assoc;
		assoc._master_type = TYPE_STREAM_CONFIG;
		assoc._master_id = stream_symbol_index;
		assoc._slave_type = TYPE_RESOLUTION_CONFIG;
		assoc._slave_id = ASSOCIATION_ALL;
		assoc._associate_type = ASSOCIATION_TYPE_DENY;
		if ( AddAssociation(handle, &assoc) < 0 ) return ERROR_CONFIG_TOO_MUCH_ENTRY;
	}

	if ( total_fps_association > 0 )
	{
		TCFGASSOCIATION assoc;
		assoc._master_type = TYPE_STREAM_CONFIG;
		assoc._master_id = stream_symbol_index;
		assoc._slave_type = TYPE_FRAMERATE_CONFIG;
		assoc._slave_id = ASSOCIATION_ALL;
		assoc._associate_type = ASSOCIATION_TYPE_DENY;
		if ( AddAssociation(handle, &assoc) < 0 ) return ERROR_CONFIG_TOO_MUCH_ENTRY;
	}

	if ( total_brc_association > 0 )
	{
		TCFGASSOCIATION assoc;
		assoc._master_type = TYPE_STREAM_CONFIG;
		assoc._master_id = stream_symbol_index;
		assoc._slave_type = TYPE_BITRATE_CONFIG;
		assoc._slave_id = ASSOCIATION_ALL;
		assoc._associate_type = ASSOCIATION_TYPE_DENY;
		if ( AddAssociation(handle, &assoc) < 0 ) return ERROR_CONFIG_TOO_MUCH_ENTRY;
	}

	if ( *line == LINE_ERROR ) return ERROR_UNKNOWN;

	error = CheckStreamConfig(handle, stream);
	if ( error != ERROR_NONE ) return error;

	stream_cap_index = FindStreamConfiguration(handle->_video_caps, stream);
	if ( stream_cap_index == -1 ) return ERROR_CONFIG_VIDEO_CAPABILITY;

	handle->_video_profiles._stream_profile_cap_index[handle->_video_profiles._num_of_stream_profiles] = stream_cap_index;
	if ( error != ERROR_NONE ) return error;

	handle->_video_profiles._num_of_stream_profiles ++;
	return ERROR_NONE;
}

enum CONFIG_ERROR CheckFrameRateConfig(PARSE_HANDLE handle, TCFGFRAMERATE* framerate)
{
	unsigned long i;

	/////////////////////////////////////////
	// check name
	/////////////////////////////////////////
	if ( (framerate->header.flags & FLAGS_NAME) == 0 || strlen(framerate->header.name) == 0 )
		return ERROR_PARSER_INVALID_ENTRY_NAME;

	for ( i = 0 ; i < handle->_video_profiles._num_of_framerate_profiles ; i ++ )
	{
		if ( strcmp(framerate->header.name, handle->_video_profiles._framerate_profiles[i].header.name) == 0 )
			return ERROR_PARSER_DUPLICATED_ENTRY_NAME;
	}

	/////////////////////////////////////////
	// check frame rate
	/////////////////////////////////////////
	if ( (framerate->header.flags & FLAGS_FRAMERATE_FRAMERATE) == 0 )
		return ERROR_PARSER_FRAMERATE_PARAMETER_MISSING;

	if ( (framerate->header.flags & FLAGS_FRAMERATE_TVSTANDARD) == 0 )
		return ERROR_PARSER_FRAMERATE_PARAMETER_MISSING;

	/////////////////////////////////////////
	// check ivtc
	/////////////////////////////////////////
	if ( (framerate->header.flags & FLAGS_FRAMERATE_IVTC_ENABLE) != 0 )
		if ( framerate->ivtc_enable != 0 ) framerate->ivtc_enable = 1;


	return ERROR_NONE;
}

enum CONFIG_ERROR ParseFrameRateConfig(PARSE_HANDLE handle, enum LINE_TYPE* line)
{
	char * __name;
	char * __value;
	TCFGFRAMERATE* framerate;
	enum CONFIG_ERROR error;
	long framerate_cap_index;
	long framerate_symbol_index;
	long total_res_association = 0;
	long total_brc_association = 0;

	if ( handle->_video_profiles._num_of_framerate_profiles >= MAX_FRAMERATE_CONFIG ) 
		return ERROR_PARSER_TOO_MUCH_CONFIG;

	framerate = &(handle->_video_profiles._framerate_profiles[handle->_video_profiles._num_of_framerate_profiles]);

	for ( ; ; )
	{
		*line = ParseLine(handle, &__name, &__value);
		if ( *line == LINE_BLANK ) continue;
		if ( *line != LINE_NAME_VALUE_PAIR ) break;

		if ( strcmp(__name, "name") == 0 )
		{
			framerate->header.flags |= FLAGS_NAME;
			strcpy(framerate->header.name, __value);

			framerate_symbol_index = AddSymbol(handle, 
									framerate->header.name, 
									TYPE_FRAMERATE_CONFIG, 
									handle->_video_profiles._num_of_framerate_profiles);

			if ( framerate_symbol_index < 0 ) return ERROR_CONFIG_TOO_MUCH_ENTRY;
			strcpy(handle->_error_context, __value);
		}
		else if ( strcmp(__name, "desc") == 0 )
		{
			framerate->header.flags |= FLAGS_DESC;
			strcpy(framerate->header.desc, __value);
		}
		else if ( strcmp(__name, "tv_standard") == 0 )
		{
			framerate->header.flags |= FLAGS_FRAMERATE_TVSTANDARD;
			if ( strcmp(__value, "NTSC") == 0 )
				framerate->tv_standard = TVStandard_NTSC_Mask;
			else if ( strcmp(__value, "PAL") == 0 )
				framerate->tv_standard = TVStandard_PAL_Mask;
			else if ( strcmp(__value, "SECAM") == 0 )
				framerate->tv_standard = TVStandard_SECAM_Mask;	
			else if ( strcmp(__value, "None") == 0 )
				framerate->tv_standard = TVStandard_None;
			else 
				return ERROR_PARSER_INVALID_TVSTANDARD;
		}
		else if ( strcmp(__name, "frame_rate") == 0 )
		{
			framerate->header.flags |= FLAGS_FRAMERATE_FRAMERATE;
			framerate->frame_rate = atoi(__value);
		}
		else if ( strcmp(__name, "drop_frame") == 0 )
		{
			framerate->header.flags |= FLAGS_FRAMERATE_DROP_FRAME;
			framerate->drop_frame = atoi(__value);
		}
		else if ( strcmp(__name, "ivtc_enable") == 0 )
		{
			framerate->header.flags |= FLAGS_FRAMERATE_IVTC_ENABLE;
			framerate->ivtc_enable = atoi(__value);
		}
		else if ( strcmp(__name, "rescfg") == 0 )
		{
			TCFGASSOCIATION assoc;
			long res_index = AddSymbol(handle, 
									__value, 
									TYPE_RESOLUTION_CONFIG, 
									-1);	// resolved later
			if ( res_index < 0 ) return ERROR_CONFIG_TOO_MUCH_ENTRY;
			assoc._master_type = TYPE_FRAMERATE_CONFIG;
			assoc._master_id = framerate_symbol_index;
			assoc._slave_type = TYPE_RESOLUTION_CONFIG;
			assoc._slave_id = res_index;
			assoc._associate_type = ASSOCIATION_TYPE_ALLOW;
			if ( AddAssociation(handle, &assoc) < 0 ) return ERROR_CONFIG_TOO_MUCH_ENTRY;
			total_res_association ++;
		}
		else if ( strcmp(__name, "ctlcfg") == 0 )
		{
			TCFGASSOCIATION assoc;
			long brc_index = AddSymbol(handle, 
									__value, 
									TYPE_BITRATE_CONFIG, 
									-1);	// resolved later
			if ( brc_index < 0 ) return ERROR_CONFIG_TOO_MUCH_ENTRY;
			assoc._master_type = TYPE_FRAMERATE_CONFIG;
			assoc._master_id = framerate_symbol_index;
			assoc._slave_type = TYPE_BITRATE_CONFIG;
			assoc._slave_id = brc_index;
			assoc._associate_type = ASSOCIATION_TYPE_ALLOW;
			if ( AddAssociation(handle, &assoc) < 0 ) return ERROR_CONFIG_TOO_MUCH_ENTRY;
			total_brc_association ++;
		}
		else
		{
			return ERROR_UNKNOWN_FRAMERATE_PARAMETER;
		}
	}

	if ( total_res_association > 0 )
	{
		TCFGASSOCIATION assoc;
		assoc._master_type = TYPE_FRAMERATE_CONFIG;
		assoc._master_id = framerate_symbol_index;
		assoc._slave_type = TYPE_RESOLUTION_CONFIG;
		assoc._slave_id = ASSOCIATION_ALL;
		assoc._associate_type = ASSOCIATION_TYPE_DENY;
		if ( AddAssociation(handle, &assoc) < 0 ) return ERROR_CONFIG_TOO_MUCH_ENTRY;
	}

	if ( total_brc_association > 0 )
	{
		TCFGASSOCIATION assoc;
		assoc._master_type = TYPE_FRAMERATE_CONFIG;
		assoc._master_id = framerate_symbol_index;
		assoc._slave_type = TYPE_BITRATE_CONFIG;
		assoc._slave_id = ASSOCIATION_ALL;
		assoc._associate_type = ASSOCIATION_TYPE_DENY;
		if ( AddAssociation(handle, &assoc) < 0 ) return ERROR_CONFIG_TOO_MUCH_ENTRY;
	}

	if ( *line == LINE_ERROR ) return ERROR_UNKNOWN;

	error = CheckFrameRateConfig(handle, framerate);
	if ( error != ERROR_NONE ) return error;
	
	framerate_cap_index = FindFrameRateConfiguration(handle->_video_caps, framerate);
	if ( framerate_cap_index == -1 ) return ERROR_CONFIG_VIDEO_CAPABILITY;

	handle->_video_profiles._framerate_profile_cap_index[handle->_video_profiles._num_of_framerate_profiles] = framerate_cap_index;
	if ( error != ERROR_NONE ) return error;


	handle->_video_profiles._num_of_framerate_profiles ++;
	return ERROR_NONE;
}

enum CONFIG_ERROR CheckBitrateConfig(PARSE_HANDLE handle, TCFGBRCTRL* bitrate)
{
	unsigned long i;

	/////////////////////////////////////////
	// check name
	/////////////////////////////////////////
	if ( (bitrate->header.flags & FLAGS_NAME) == 0 || strlen(bitrate->header.name) == 0 )
		return ERROR_PARSER_INVALID_ENTRY_NAME;

	for ( i = 0 ; i < handle->_video_profiles._num_of_bitrate_profiles ; i ++ )
	{
		if ( strcmp(bitrate->header.name, handle->_video_profiles._bitrate_profiles[i].header.name) == 0 )
			return ERROR_PARSER_DUPLICATED_ENTRY_NAME;
	}

	/////////////////////////////////////////
	// check target bitrate
	/////////////////////////////////////////
	if ( (bitrate->header.flags & FLAGS_BITRATE_TARGET) == 0 )
		return ERROR_PARSER_BITRATE_PARAMETER_MISSING;

	/////////////////////////////////////////
	// check initial Q value
	/////////////////////////////////////////
	if ( (bitrate->header.flags & FLAGS_BITRATE_Q) == 0 )
		return ERROR_PARSER_BITRATE_PARAMETER_MISSING;

/*
	if ( bitrate->target_bitrate == 0 && bitrate->Q == 0 )
		return ERROR_PARSER_BITRATE_TARGET_BITRATE;
*/
	/////////////////////////////////////////
	// check peak bitrate
	/////////////////////////////////////////
	if ( (bitrate->header.flags & FLAGS_BITRATE_PEAK) != 0 )
	{
		if ( bitrate->target_bitrate > bitrate->peak_bitrate )
			return ERROR_PARSER_BITRATE_PEAK_BITRATE;
	}

	/////////////////////////////////////////
	// check converge speed
	/////////////////////////////////////////
	if ( (bitrate->header.flags & FLAGS_BITRATE_CONVERGE_SPEED) != 0 )
	{
		if ( bitrate->converge_speed > 100 || bitrate->converge_speed < 0 )
			return ERROR_PARSER_BITRATE_CONVERGE_SPEED;
	}

	/////////////////////////////////////////
	// check lambda
	/////////////////////////////////////////
	if ( ( bitrate->header.flags & FLAGS_BITRATE_LAMBDA ) != 0 )
	{
		if ( bitrate->lambda > 100 || bitrate->lambda < 0 )
			return ERROR_PARSER_BITRATE_LAMBDA;
	}

	/////////////////////////////////////////
	// check Q
	/////////////////////////////////////////
	#define FLAGS_BITRATE_QQQ  ( FLAGS_BITRATE_IQ | FLAGS_BITRATE_PQ | FLAGS_BITRATE_BQ )
	if ( ( bitrate->header.flags & FLAGS_BITRATE_QQQ ) == FLAGS_BITRATE_QQQ )
	{
		bitrate->header.flags |= FLAGS_BITRATE_IPBQ;
		if ( bitrate->IQ > 32 || bitrate->IQ < 1
			|| bitrate->PQ > 32 || bitrate->PQ < 1
			|| bitrate->BQ > 32 || bitrate->BQ < 1 )
			return ERROR_PARSER_BITRATE_Q;
	}
	else if ( ( bitrate->header.flags & FLAGS_BITRATE_QQQ ) != 0 )
	{
		return ERROR_PARSER_BITRATE_Q;
	}

	return ERROR_NONE;
}

enum CONFIG_ERROR ParseBitrateConfig(PARSE_HANDLE handle, enum LINE_TYPE* line)
{
	char * __name;
	char * __value;
	UINT32 value;
	TCFGBRCTRL* bitrate;
	enum CONFIG_ERROR error;
	long bitrate_symbol_index;

	if ( handle->_video_profiles._num_of_bitrate_profiles >= MAX_BITRATE_CONFIG ) 
		return ERROR_PARSER_TOO_MUCH_CONFIG;

	bitrate = &(handle->_video_profiles._bitrate_profiles[handle->_video_profiles._num_of_bitrate_profiles]);

	for ( ; ; )
	{
		*line = ParseLine(handle, &__name, &__value);
		if ( *line == LINE_BLANK ) continue;
		if ( *line != LINE_NAME_VALUE_PAIR ) break;

		if ( strcmp(__name, "name") == 0 )
		{
			bitrate->header.flags |= FLAGS_NAME;
			strcpy(bitrate->header.name, __value);

			bitrate_symbol_index = AddSymbol(handle, 
									bitrate->header.name, 
									TYPE_BITRATE_CONFIG, 
									handle->_video_profiles._num_of_bitrate_profiles);

			if ( bitrate_symbol_index < 0 ) return ERROR_CONFIG_TOO_MUCH_ENTRY;
			strcpy(handle->_error_context, __value);
		}
		else if ( strcmp(__name, "desc") == 0 )
		{
			bitrate->header.flags |= FLAGS_DESC;
			strcpy(bitrate->header.desc, __value);
		}
		else if ( strcmp(__name, "target_bitrate") == 0 )
		{
			bitrate->header.flags |= FLAGS_BITRATE_TARGET;
			bitrate->target_bitrate = atoi(__value);
		}
		else if ( strcmp(__name, "peak_bitrate") == 0 )
		{
			bitrate->header.flags |= FLAGS_BITRATE_PEAK;
			bitrate->peak_bitrate = atoi(__value);
		}
		else if ( strcmp(__name, "vbv_buffer") == 0 )
		{
			bitrate->header.flags |= FLAGS_BITRATE_VBV_BUFFER;
			bitrate->vbv_buffer = atoi(__value);
		}
		else if ( strcmp(__name, "converge_speed") == 0 )
		{
			bitrate->header.flags |= FLAGS_BITRATE_CONVERGE_SPEED;
			bitrate->converge_speed = atoi(__value);
		}
		else if ( strcmp(__name, "lambda") == 0 )
		{
			bitrate->header.flags |= FLAGS_BITRATE_LAMBDA;
			bitrate->lambda = atoi(__value);
		}
		else if ( strcmp(__name, "Q") == 0 )
		{
			bitrate->header.flags |= FLAGS_BITRATE_Q;
			bitrate->Q = atoi(__value);
		}
		else if ( strcmp(__name, "IQ") == 0 )
		{
			bitrate->header.flags |= FLAGS_BITRATE_IQ;
			bitrate->IQ = atoi(__value);
		}
		else if ( strcmp(__name, "PQ") == 0 )
		{
			bitrate->header.flags |= FLAGS_BITRATE_PQ;
			bitrate->PQ = atoi(__value);
		}
		else if ( strcmp(__name, "BQ") == 0 )
		{
			bitrate->header.flags |= FLAGS_BITRATE_BQ;
			bitrate->BQ = atoi(__value);
		}
		else if ( strcmp(__name, "QMin") == 0 )
		{
			bitrate->header.flags |= FLAGS_BITRATE_QMIN;
			value = atoi(__value);
			value &= 0x7F;
			bitrate->reserved |= value;
		}
		else if ( strcmp(__name, "QMax") == 0 )
		{
			bitrate->header.flags |= FLAGS_BITRATE_QMAX;
			value = atoi(__value);
			value &= 0x7F;
			bitrate->reserved |= (value << 8);
		}
		else if ( strcmp(__name, "Duplicate") == 0 )
		{
			bitrate->header.flags |= FLAGS_BITRATE_DUP_ENABLE;
			value = ( atoi(__value) > 0 ) ? 0x80 : 0x0 ;
			bitrate->reserved |= value;
		}
		else if ( strcmp(__name, "MBBrc") == 0 )
		{
			bitrate->header.flags |= FLAGS_BITRATE_MBBRC_ENABLE;
			value = ( atoi(__value) > 0 ) ? 0x8000 : 0x0 ;
			bitrate->reserved |= value;
		}
		else if ( strcmp(__name, "WindowSize") == 0 )
		{
			bitrate->header.flags |= FLAGS_BITRATE_BRC_WINDOW;
			value = atoi(__value);
			value &= 0xFFFF;
			bitrate->reserved |= (value << 16);
		}
		else
		{
			return ERROR_UNKNOWN_BITRATE_PARAMETER;
		}
	}

	if ( *line == LINE_ERROR ) return ERROR_UNKNOWN;

	error = CheckBitrateConfig(handle, bitrate);
	if ( error != ERROR_NONE ) return error;
	
//	bitrate_cap_index = FindBitRateConfiguration(handle->_video_caps, bitrate);
//	if ( bitrate_cap_index == -1 ) return ERROR_CONFIG_VIDEO_CAPABILITY;

	handle->_video_profiles._num_of_bitrate_profiles ++;
	return ERROR_NONE;
}

enum CONFIG_ERROR CheckResolutionConfig(PARSE_HANDLE handle, TCFGRESOLUTION* resolution)
{
	unsigned long i;

	/////////////////////////////////////////
	// check name
	/////////////////////////////////////////
	if ( (resolution->header.flags & FLAGS_NAME) == 0 || strlen(resolution->header.name) == 0 )
		return ERROR_PARSER_INVALID_ENTRY_NAME;

	for ( i = 0 ; i < handle->_video_profiles._num_of_resolution_profiles ; i ++ )
	{
		if ( strcmp(resolution->header.name, handle->_video_profiles._resolution_profiles[i].header.name) == 0 )
			return ERROR_PARSER_DUPLICATED_ENTRY_NAME;
	}

	/////////////////////////////////////////
	// check width
	/////////////////////////////////////////
	if ( (resolution->header.flags & FLAGS_RESOLUTION_WIDTH) == 0 )
		return ERROR_PARSER_RESOLUTION_PARAMETER_MISSING;

	/////////////////////////////////////////
	// check height
	/////////////////////////////////////////
	if ( (resolution->header.flags & FLAGS_RESOLUTION_HEIGHT) == 0 )
		return ERROR_PARSER_RESOLUTION_PARAMETER_MISSING;

	/////////////////////////////////////////
	// check tv standard
	/////////////////////////////////////////
	if ( (resolution->header.flags & FLAGS_RESOLUTION_TVSTANDARD) == 0 )
		return ERROR_PARSER_RESOLUTION_PARAMETER_MISSING;

	/////////////////////////////////////////
	// check maximum and minimum bitrate
	/////////////////////////////////////////
/*	if ( (resolution->header.flags & FLAGS_RESOLUTION_MAX_BITRATE) == 0 )
		return ERROR_PARSER_RESOLUTION_PARAMETER_MISSING;
	if ( (resolution->header.flags & FLAGS_RESOLUTION_MIN_BITRATE) == 0 )
		return ERROR_PARSER_RESOLUTION_PARAMETER_MISSING;
	if ( resolution->max_bitrate < resolution->min_bitrate ) 
		return ERROR_PARSER_RESOLUTION_BITRATE_RANGE;
*/
	resolution->header.flags |= FLAGS_RESOLUTION_MAX_BITRATE | FLAGS_RESOLUTION_MIN_BITRATE ;

	/////////////////////////////////////////
	// check h/v sub window & sub sample
	/////////////////////////////////////////
	if ( (resolution->header.flags & FLAGS_RESOLUTION_H_SUBWINDOW) == 0 )
		resolution->h_sub_window = 1;
	if ( (resolution->header.flags & FLAGS_RESOLUTION_V_SUBWINDOW) == 0 )
		resolution->v_sub_window = 1;	
	if ( (resolution->header.flags & FLAGS_RESOLUTION_SUBSAMPLE) == 0 )
		resolution->v_sub_window = 0;	

	/////////////////////////////////////////
	// check scale and offset
	/////////////////////////////////////////
	#define FLAGS_RESOLUTION_SCALE_OFFSET_ALL (FLAGS_RESOLUTION_H_SUBOFFSET \
											| FLAGS_RESOLUTION_V_SUBOFFSET \
											| FLAGS_RESOLUTION_H_SCALE_ENABLE \
											| FLAGS_RESOLUTION_V_SCALE_ENABLE)

	if ( ( resolution->header.flags & FLAGS_RESOLUTION_SCALE_OFFSET_ALL ) == FLAGS_RESOLUTION_SCALE_OFFSET_ALL )
	{
		resolution->header.flags |= FLAGS_RESOLUTION_SCALE_OFFSET;
	}
	else if ( ( resolution->header.flags & FLAGS_RESOLUTION_SCALE_OFFSET_ALL ) != 0 )
	{
		return ERROR_PARSER_RESOLUTION_SCALE_OFFSET;
	}


	return ERROR_NONE;
}

enum CONFIG_ERROR ParseResolutionConfig(PARSE_HANDLE handle, enum LINE_TYPE* line)
{
	char * __name;
	char * __value;
	TCFGRESOLUTION* resolution;
	enum CONFIG_ERROR error;
	long resolution_cap_index;
	long resolution_symbol_index;
	long total_brc_association = 0;

	if ( handle->_video_profiles._num_of_resolution_profiles >= MAX_RESOLUTION_CONFIG ) 
		return ERROR_PARSER_TOO_MUCH_CONFIG;

	resolution = &(handle->_video_profiles._resolution_profiles[handle->_video_profiles._num_of_resolution_profiles]);

	for ( ; ; )
	{
		*line = ParseLine(handle, &__name, &__value);
		if ( *line == LINE_BLANK ) continue;
		if ( *line != LINE_NAME_VALUE_PAIR ) break;

		if ( strcmp(__name, "name") == 0 )
		{
			resolution->header.flags |= FLAGS_NAME;
			strcpy(resolution->header.name, __value);

			resolution_symbol_index = AddSymbol(handle, 
									resolution->header.name, 
									TYPE_RESOLUTION_CONFIG, 
									handle->_video_profiles._num_of_resolution_profiles);

			if ( resolution_symbol_index < 0 ) return ERROR_CONFIG_TOO_MUCH_ENTRY;
			strcpy(handle->_error_context, __value);
		}
		else if ( strcmp(__name, "desc") == 0 )
		{
			resolution->header.flags |= FLAGS_DESC;
			strcpy(resolution->header.desc, __value);

		}
		else if ( strcmp(__name, "tv_standard") == 0 )
		{
			resolution->header.flags |= FLAGS_RESOLUTION_TVSTANDARD;
			resolution->header.flags |= FLAGS_FRAMERATE_TVSTANDARD;
			if ( strcmp(__value, "NTSC") == 0 )
				resolution->tv_standard = TVStandard_NTSC_Mask;
			else if ( strcmp(__value, "PAL") == 0 )
				resolution->tv_standard = TVStandard_PAL_Mask;
			else if ( strcmp(__value, "SECAM") == 0 )
				resolution->tv_standard = TVStandard_SECAM_Mask;
			else if ( strcmp(__value, "None") == 0 )
				resolution->tv_standard = TVStandard_None;
			else 
				return ERROR_PARSER_INVALID_TVSTANDARD;
		}
		else if ( strcmp(__name, "width") == 0 )
		{
			resolution->header.flags |= FLAGS_RESOLUTION_WIDTH;
			resolution->width = atoi(__value);
		}
		else if ( strcmp(__name, "height") == 0 )
		{
			resolution->header.flags |= FLAGS_RESOLUTION_HEIGHT;
			resolution->height = atoi(__value);
		}
		else if ( strcmp(__name, "h_sub_window") == 0 )
		{
			resolution->header.flags |= FLAGS_RESOLUTION_H_SUBWINDOW;
			resolution->h_sub_window = atoi(__value);
		}
		else if ( strcmp(__name, "v_sub_window") == 0 )
		{
			resolution->header.flags |= FLAGS_RESOLUTION_V_SUBWINDOW;
			resolution->v_sub_window = atoi(__value);
		}
		else if ( strcmp(__name, "h_sub_offset") == 0 )
		{
			resolution->header.flags |= FLAGS_RESOLUTION_H_SUBOFFSET;
			resolution->h_sub_offset = atoi(__value);
		}
		else if ( strcmp(__name, "v_sub_offset") == 0 )
		{
			resolution->header.flags |= FLAGS_RESOLUTION_V_SUBOFFSET;
			resolution->v_sub_offset = atoi(__value);
		}
		else if ( strcmp(__name, "h_scale_enb") == 0 )
		{
			resolution->header.flags |= FLAGS_RESOLUTION_H_SCALE_ENABLE;
			resolution->h_scale_enb = atoi(__value);
		}
		else if ( strcmp(__name, "v_scale_enb") == 0 )
		{
			resolution->header.flags |= FLAGS_RESOLUTION_V_SCALE_ENABLE;
			resolution->v_scale_enb = atoi(__value);
		}
		else if ( strcmp(__name, "sub_sample") == 0 )
		{
			resolution->header.flags |= FLAGS_RESOLUTION_SUBSAMPLE;
			resolution->sub_sample = atoi(__value);
		}
		else if ( strcmp(__name, "max_bitrate") == 0 )
		{
			resolution->header.flags |= FLAGS_RESOLUTION_MAX_BITRATE;
			resolution->max_bitrate = atoi(__value);
		}
		else if ( strcmp(__name, "min_bitrate") == 0 )
		{
			resolution->header.flags |= FLAGS_RESOLUTION_MIN_BITRATE;
			resolution->min_bitrate = atoi(__value);
		}
		else if ( strcmp(__name, "ctlcfg") == 0 )
		{
			TCFGASSOCIATION assoc;
			long brc_index = AddSymbol(handle, 
									__value, 
									TYPE_BITRATE_CONFIG, 
									-1);	// resolved later
			if ( brc_index < 0 ) return ERROR_CONFIG_TOO_MUCH_ENTRY;
			assoc._master_type = TYPE_RESOLUTION_CONFIG;
			assoc._master_id = resolution_symbol_index;
			assoc._slave_type = TYPE_BITRATE_CONFIG;
			assoc._slave_id = brc_index;
			assoc._associate_type = ASSOCIATION_TYPE_ALLOW;
			if ( AddAssociation(handle, &assoc) < 0 ) return ERROR_CONFIG_TOO_MUCH_ENTRY;
			total_brc_association ++;
		}
		else
		{
			return ERROR_UNKNOWN_RESOLUTION_PARAMETER;
		}
	}

	if ( total_brc_association > 0 )
	{
		TCFGASSOCIATION assoc;
		assoc._master_type = TYPE_RESOLUTION_CONFIG;
		assoc._master_id = resolution_symbol_index;
		assoc._slave_type = TYPE_BITRATE_CONFIG;
		assoc._slave_id = ASSOCIATION_ALL;
		assoc._associate_type = ASSOCIATION_TYPE_DENY;
		if ( AddAssociation(handle, &assoc) < 0 ) return ERROR_CONFIG_TOO_MUCH_ENTRY;
	}

	if ( *line == LINE_ERROR ) return ERROR_UNKNOWN;

	error = CheckResolutionConfig(handle, resolution);
	if ( error != ERROR_NONE ) return error;
	
	resolution_cap_index = FindResolutionConfiguration(handle->_video_caps, resolution);
	if ( resolution_cap_index == -1 ) return ERROR_CONFIG_VIDEO_CAPABILITY;

	handle->_video_profiles._resolution_profile_cap_index[handle->_video_profiles._num_of_resolution_profiles] = resolution_cap_index;
	if ( error != ERROR_NONE ) return error;

	handle->_video_profiles._num_of_resolution_profiles ++;
	return ERROR_NONE;
}

PARSE_HANDLE OpenConfigurationFile(const char* szFilePath)
{
	if ( access(szFilePath, 0) != 0 ) return NULL;

	__gHandle._fp = fopen(szFilePath, "rt");
	if ( __gHandle._fp == NULL ) return NULL;

	__gHandle._last_error = ERROR_NONE;
	__gHandle._line_number = 0;

	memset(&__gHandle._header, 0, sizeof(struct CONFIG_FILE_HEADER));
	memset(&__gHandle._video_profiles, 0, sizeof(__gHandle._video_profiles));

	__gHandle._num_of_symbols = 0;
	memset(&__gHandle._symbols, 0, sizeof(__gHandle._symbols));

	__gHandle._header._file_version = 1;

	return &__gHandle;
}

void CloseConfigurationFile(PARSE_HANDLE handle)
{
//	unsigned long i;

	fclose(handle->_fp);
	handle->_last_error = ERROR_NONE;
	handle->_line_number = 0;

//	for ( i = 0 ; i < handle->_num_of_symbols ; i ++ )
//		free(handle->_symbols[i]._name);
}

enum CONFIG_ERROR ParseConfigurationFile(PARSE_HANDLE handle, _VIDEO_CAPABILITIES* caps, _VIDEO_PROFILES* profiles)
{
	enum LINE_TYPE line = LINE_BLANK;

	if ( __gHandle._fp == NULL ) return handle->_last_error = ERROR_FILE_NOT_EXIST;

	__gHandle._video_caps = caps;

	for ( ; feof(handle->_fp) == 0; )	// the end of file has not been reached
	{
		if ( line == LINE_BLANK ) line = ParseLine(handle, NULL, NULL);
		if ( line == LINE_END ) break;
		switch ( line )
		{
			case LINE_BLANK:
				continue;
			case LINE_STREAM_SECTION:
				handle->_last_error = ParseStreamConfig(handle, &line);
				break;
			case LINE_FRAMERATE_SECTION:
				handle->_last_error = ParseFrameRateConfig(handle, &line);
				break;
			case LINE_RESOLUTION_SECTION:
				handle->_last_error = ParseResolutionConfig(handle, &line);
				break;
			case LINE_BITRATE_SECTION:
				handle->_last_error = ParseBitrateConfig(handle, &line);
				break;
			case LINE_ERROR:
			case LINE_NAME_VALUE_PAIR:
			default:
				return handle->_last_error = ERROR_FILE_CORRUPTED;
		}
		if ( handle->_last_error != ERROR_NONE && handle->_last_error != ERROR_CONFIG_VIDEO_CAPABILITY ) break;
	}

//	if ( handle->_last_error == ERROR_NONE ) handle->_last_error = ResolveSymbols(handle);
//	if ( handle->_last_error == ERROR_NONE ) DumpAssociations(handle);

	*profiles = handle->_video_profiles;

	return handle->_last_error;
}

enum CONFIG_ERROR GetParseErrorInformation(PARSE_HANDLE handle, UINT32* line)
{
	if ( line != NULL ) *line = handle->_line_number;
	return handle->_last_error;
}

/************************** end of config_text_parser.c **********************/

