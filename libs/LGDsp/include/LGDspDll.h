


//
// ****************************************************************************
//                          C O N F I D E N T I A L
//  Copyright (c) 2014-2016 LaserAnimation Sollinger GmbH, all rights reserved
// ****************************************************************************
//
// Do not redistribute!
//
// Redistribution of any of the files "LGDspDll.h" , "LGDsp.dll" or "LGDsp.lib"
// requires written permission by LaserAnimation Sollinger GmbH.
//
// http://www.laseranimation.com
//



//
// Overview
// ========
//
//   LGDspDll_SelectDialog          Opens a dialog to select a Lasergraph DSP.
//   LGDspDll_Connect               Establishes a connection with a Lasergraph DSP.
//   LGDspDll_GetLastError          Gets a detailed error message after a function call has failed.
//   LGDspDll_LoadBoot              Loads the specified BOOT into the Lasergraph DSP.
//   LGDspDll_SetPicture            Transmits a picture to the Lasergraph DSP.
//   LGDspDll_SetPictureRGB         Transmits a true color picture to the Lasergraph DSP.
//   LGDspDll_SetGlobalValue        Sets a "Global Value" to the specified value.
//   LGDspDll_GetGlobalValue        Gets the current value of a "Global Value".
//   LGDspDll_SetGlobalValues       Sets one or more consecutive global values.
//   LGDspDll_GetGlobalValues       Gets one or more consecutive global values.
//   LGDspDll_SetFaderValues        Sets one or more consecutive fader values.
//   LGDspDll_GetFaderValues        Gets one or more consecutive fader values.
//   LGDspDll_SetFaderButtons       Sets the state of one or more consecutive fader buttons.
//   LGDspDll_GetFaderButtons       Gets the state of one or more consecutive fader buttons.
//   LGDspDll_SetSharedVars         Sets one or more consecutive shared variables.
//   LGDspDll_GetSharedVars         Gets one or more consecutive shared variables.
//   LGDspDll_SetDmxOut             Sets one or more DMX output channels.
//   LGDspDll_SetGlobalText         Modifies a text in the "Global Text Table".
//   LGDspDll_GetEntries            Determines which entries are available in the specified Trickfilm.
//   LGDspDll_GetEntryName          Gets the name of the specified entry.
//   LGDspDll_GetAnimationNames     Determines the names of all loaded animations.
//   LGDspDll_GetNextAnimationName  Gets the name of the next loaded animation.
//   LGDspDll_GetCatalogNames       Determines the names of all loaded catalogs.
//   LGDspDll_GetNextCatalogName    Gets the name of the next loaded catalog.
//   LGDspDll_GetPictureNames       Determines the names of all loaded pictures within the specified catalog.
//   LGDspDll_GetNextPictureName    Gets the name of the next loaded picture.
//   LGDspDll_Goto                  Starts an entry in the specified Trickfilm.
//   LGDspDll_ExeCmd                Enters a command into the command line and executes it.
//






    



//
// LGDspDll_SelectDialog
// =====================
//
//   Description:
//
//      Opens a dialog so select a Lasergraph DSP.
//
//   Parameters:
//
//      name_or_ip_address   Pointer to a buffer to which the name and/or the ip address of the selected 
//                           Lasergraph DSP is to be written.
//
//      buffer_size          Size of the buffer in characters. If the buffer is not large enough for
//                           the entire string the string will be truncated.
//
//   Return Value:
//
//      If the user selects "Connect", the function returns true.
//      If the user selects "Cancel", the function returns false.
//
//   Required System Software:
//
//      Available on all Mark 2.
//
extern "C" __declspec(dllimport) bool __cdecl LGDspDll_SelectDialog (char *name_or_ip_address, int buffer_size);



//
// LGDspDll_Connect
// ================
//
//   Description:
//
//      Establishes a connection with a Lasergraph DSP.
//      This function has to be called before any of the following functions is called.
//      
//   Parameters:
//
//      name_or_ip_address   This can either be the network name of the Lasergraph DSP (e.g. "MyCompact")
//                           or the IP address of the Lasergraph DSP (e.g. "192.168.1.100").
//
//      cmd_timeout          Specifies the command timeout in 1/100s for all following commands.
//                           Allow at least 2 seconds, extend this for commands that may take longer.
//                           The default timeout is 10 seconds (10 * 100).
//
//   Return Value:
//
//      If the function succeeds, it returns true.
//      If the function fails, it returns false. For extended error information call "LGDspDll_GetLastError".
//
//   Required System Software:
//
//      Available on all Mark 2.
//
extern "C" __declspec(dllimport) bool __cdecl LGDspDll_Connect (const char *name_or_ip_address, long cmd_timeout = 10 * 100);



//
// LGDspDll_GetLastError
// =======================
//
//   Description:
//
//      This function can be used to get a detailed error message after a function call has failed. 
//
//   Parameters:
//
//      buffer               Pointer to the buffer to which the error message is to be written.
//
//      buffer_size          Size of the buffer in characters. If the buffer is not large enough
//                           for the entire error message the error message will be truncated.
//
//   Return Value:
//
//      Returns true if an error occurred during the last function call.
//
//   Required System Software:
//
//      Available on all Mark 2.
//
extern "C" __declspec(dllimport) bool __cdecl LGDspDll_GetLastError (char *buffer, int buffer_size);



//
// LGDspDll_LoadBoot
// =================
//
//   Description:
//
//      Loads the specified BOOT into the Lasergraph DSP.
//      A BOOT is a directory created with the command "CreateBoot" that contains
//      all of the information loaded at the time of creation.
//
//      The parameter "boot_name" may contain relative or absolute paths.
//      The extension ".BOOT" is automatically appended to "boot_name".
//
//      Examples:
//
//        "Test"                        loads the BOOT "Test.BOOT" from the current
//                                      directory of the Lasergraph DSP.
//
//        "Dir\Test"                    loads the BOOT "Test.BOOT" from the sub-directory
//                                      "Dir" based on the current directory of the
//                                      Lasergraph DSP.
//
//        "\\MyComputer\MyShare\Test"   loads the BOOT "Test.BOOT" from the share 
//                                      "MyShare" of the computer "MyComputer".
//
//      Note: Depending on the BOOT to load it might be necessary to temporarily 
//            increase the command timeout using "LGDspDll_SetCmdTimeout".
//            
//   Parameters:
//
//      boot_name            Name of the BOOT to load.
//
//                           The name of the BOOT has to be specified in the DSP-format, i.e. all
//                           characters with an ACII-code >32 are legal, except: " * . / : < > ? \ |
//
//                           Additionally the length of the name of the BOOT and the length of each
//                           part of the path must not exceed 14+4 (name+extenstion) characters.
//                           
//      flags                Bit 0:  Overwrite
//                                     0 = Abort if the loaded information has been edited and not yet saved
//                                     1 = Silently discard loaded information, even if it has been edited and not yet saved
//
//                           Others: Not yet defined, must be '0'
//
//   Return Value:
//
//      If the function succeeds, it returns true.
//      If the function fails, it returns false. For extended error information call "LGDspDll_GetLastError".
//
//   Required System Software:
//
//      2014/05/15 or newer.
//
extern "C" __declspec(dllimport) bool __cdecl LGDspDll_LoadBoot (const char *boot_name, unsigned long flags);



//
// LGDspDll_SetPicture
// ===================
//
//   Description:
//
//      Transmits a picture to the Lasergraph DSP.
//      The picture is stored in the picture memory of the Lasergraph DSP in the
//      specified catalog under the specified name. If a picture with the same
//      name already exists in this catalog it will be overwritten.
//
//   Parameters:
//
//      catalog_name         Name of the catalog where the picture is to be stored.
//                           The catalog name has to be specified in the DSP-format, i.e. all
//                           characters with an ACII-code >32 are legal, except: " * . / : < > ? \ |
//
//      picture_name         Name of the picture.
//                           The picture name has to be specified in the DSP-format, i.e. all
//                           characters with an ACII-code >32 are legal, except: " * . / : < > ? \ |
//
//      number_of_points     Number of points the picture contains.
//                           Allowed range: 1...4096
//
//      point_array          Pointer to an array of the type "DspPoint".
//                           The array must contain the same number of elements as specified
//                           by "number_of_points".
//
//   Return Value:
//
//      If the function succeeds, it returns true.
//      If the function fails, it returns false. For extended error information call "LGDspDll_GetLastError".
//
//   Required System Software:
//
//      Available on all Mark 2.
//

// forward declaration
class DspPoint;

extern "C" __declspec(dllimport) bool __cdecl LGDspDll_SetPicture (const char *catalog_name, const char *picture_name,
                                                       int number_of_points, const DspPoint *point_array);



//
// LGDspDll_SetPictureRGB
// ======================
//
//   Description:
//
//      Transmits a true color picture to the Lasergraph DSP.
//      The picture is stored in the picture memory of the Lasergraph DSP in the
//      specified catalog under the specified name. If a picture with the same
//      name already exists in this catalog it will be overwritten.
//
//   Parameters:
//
//      catalog_name         Name of the catalog where the picture is to be stored.
//                           The catalog name has to be specified in the DSP-format, i.e. all
//                           characters with an ACII-code >32 are legal, except: " * . / : < > ? \ |
//
//      picture_name         Name of the picture.
//                           The picture name has to be specified in the DSP-format, i.e. all
//                           characters with an ACII-code >32 are legal, except: " * . / : < > ? \ |
//
//      number_of_points     Number of points the picture contains.
//                           Allowed range: 1...4096
//
//      point_array          Pointer to an array of the type "DspPointRGB".
//                           The array must contain the same number of elements as specified
//                           by "number_of_points".
//
//   Return Value:
//
//      If the function succeeds, it returns true.
//      If the function fails, it returns false. For extended error information call "LGDspDll_GetLastError".
//
//   Required System Software:
//
//      Available on all Mark 2.
//

// forward declaration
class DspPointRGB;

extern "C" __declspec(dllimport) bool __cdecl LGDspDll_SetPictureRGB (const char *catalog_name, const char *picture_name,
                                                          int number_of_points, const DspPointRGB *point_array);



//
// LGDspDll_SetGlobalValue
// =======================
//
//   Description:
//
//      Sets a "Global Value" to the specified value.
//
//   Parameters:
//
//      number               Number of the "Global Value" which is to be set. 
//                           Allowed range: 0...1000000
//
//      value                Value the "Global Value" is to be set to.
//
//   Return Value:
//
//      If the function succeeds, it returns true.
//      If the function fails, it returns false. For extended error information call "LGDspDll_GetLastError".
//
//   Required System Software:
//
//      Available on all Mark 2.
//
extern "C" __declspec(dllimport) bool __cdecl LGDspDll_SetGlobalValue (int number, double value);



//
// LGDspDll_GetGlobalValue
// =======================
//
//   Description:
//
//      Gets the current value of a "Global Value".
//
//   Parameters:
//
//      number               Number of the "Global Value" which is to be queried. 
//                           Allowed range: 0...1000000
//
//      value                Reference to the variable where the current value of
//                           the specified "Global Value" is stored.
//
//   Return Value:
//
//      If the function succeeds, it returns true.
//      If the function fails, it returns false. For extended error information call "LGDspDll_GetLastError".
//
//   Required System Software:
//
//      Available on all Mark 2.
//
extern "C" __declspec(dllimport) bool __cdecl LGDspDll_GetGlobalValue (int number, double &value);



//
// LGDspDll_SetGlobalValues
// ========================
//
//   Description:
//
//      Sets one or more consecutive global values.
//
//   Parameters:
//
//      first_value          Number of the first global value which is to be set. 
//                           Allowed range: 0...1000000
//
//      count                Number of global values which are to be set.
//                           Allowed range: 1...64
//
//                           Note: All global values to be set have to be in the 0...1000000 range.
//
//      value_array          Pointer to an array of values to which the global values are to be set.
//
//   Return Value:
//
//      If the function succeeds, it returns true.
//      If the function fails, it returns false. For extended error information call "LGDspDll_GetLastError".
//
//   Required System Software:
//
//      Available on all Mark 2.
//
extern "C" __declspec(dllimport) bool __cdecl LGDspDll_SetGlobalValues (int first_value, int count, const double *value_array);



//
// LGDspDll_GetGlobalValues
// ========================
//
//   Description:
//
//      Gets one or more consecutive global values.
//
//   Parameters:
//
//      first_value          Number of the first global value which is to be queried. 
//                           Allowed range: 0...1000000
//
//      count                Number of global values which are to be queried.
//                           Allowed range: 1...64
//
//                           Note: All global values queried have to be in the 0...1000000 range.
//
//      value_array          Pointer to an array where the global values are to be stored.
//
//   Return Value:
//
//      If the function succeeds, it returns true.
//      If the function fails, it returns false. For extended error information call "LGDspDll_GetLastError".
//
//   Required System Software:
//
//      2014/07/08 or newer.
//
extern "C" __declspec(dllimport) bool __cdecl LGDspDll_GetGlobalValues (int first_value, int count, double *value_array);



//
// LGDspDll_SetFaderValues
// =======================
//
//   Description:
//
//      Sets one or more consecutive fader values.
//      The Lasergraph DSP supports 64 faders with 16 bit resolution each.
//      The values are presented to the user in the range from 0.000 to 1.000:
//
//          Internal            User Interface
//          --------            --------------
//
//          $0000 = 0           0.000
//          ...                 ...
//          $8000 = 32768       0.500
//          ...                 ...
//          $FFFF = 65535       1.000
//
//      Note: Value changes are handled by the Lasergraph DSP in the same way as
//            changes that are triggered by an externally connected fader board.
//            Therefore the new values are automatically sent to all Lasergraph DSPs
//            where this Lasergraph DSP is entered as server in the "I/O Setup".
//
//      Note: The current state of all fader values can be displayed on the
//            Lasergraph DSP using the command "IOINFO".
//
//   Parameters:
//
//      first_fader          Number of the first fader which is to be set. 
//                           Allowed range: 0...63
//
//      count                Number of fader values which are to be set.
//                           Allowed range: 1...64
//
//                           Note: All faders to be set have to be in the 0...63 range.
//
//      value_array          Pointer to an array of values to which the faders are to be set.
//
//   Return Value:
//
//      If the function succeeds, it returns true.
//      If the function fails, it returns false. For extended error information call "LGDspDll_GetLastError".
//
//   Required System Software:
//
//      2014/05/15 or newer.
//
extern "C" __declspec(dllimport) bool __cdecl LGDspDll_SetFaderValues (int first_fader, int count, const unsigned short *value_array);



//
// LGDspDll_GetFaderValues
// =======================
//
//   Description:
//
//      Gets one or more consecutive fader values.
//      The Lasergraph DSP supports 64 faders with 16 bit resolution each.
//      The values are presented to the user in the range from 0.000 to 1.000:
//
//          Internal            User Interface
//          --------            --------------
//
//          $0000 = 0           0.000
//          ...                 ...
//          $8000 = 32768       0.500
//          ...                 ...
//          $FFFF = 65535       1.000
//
//   Parameters:
//
//      first_fader          Number of the first fader which is to be queried. 
//                           Allowed range: 0...63
//
//      count                Number of fader values which are to be queried.
//                           Allowed range: 1...64
//
//                           Note: All faders queried have to be in the 0...63 range.
//
//      value_array          Pointer to an array where the fader values are to be stored.
//
//   Return Value:
//
//      If the function succeeds, it returns true.
//      If the function fails, it returns false. For extended error information call "LGDspDll_GetLastError".
//
//   Required System Software:
//
//      2014/05/15 or newer.
//
extern "C" __declspec(dllimport) bool __cdecl LGDspDll_GetFaderValues (int first_fader, int count, unsigned short *value_array);



//
// LGDspDll_SetFaderButtons
// ========================
//
//   Description:
//
//      Sets the state of one or more consecutive fader buttons.
//      Each fader button can be either pressed (true) or released (false).
//      The Lasergraph DSP supports 64 fader buttons.
//
//      Note: State changes are handled by the Lasergraph DSP in the same way as
//            changes that are triggered by an externally connected fader board.
//            Therefore the new states are automatically sent to all Lasergraph DSPs
//            where this Lasergraph DSP is entered as server in the "I/O Setup".
//
//      Note: The current state of all fader buttons can be displayed on the
//            Lasergraph DSP using the command "IOINFO".
//
//   Parameters:
//
//      first_button         Number of the first fader button whose state is to be set. 
//                           Allowed range: 0...63
//
//      count                Number of fader buttons whose states are to be set.
//                           Allowed range: 1...64
//
//                           Note: All fader buttons to be set have to be in the 0...63 range.
//
//      value_array          Pointer to an array of states to which the fader buttons are to be set.
//
//   Return Value:
//
//      If the function succeeds, it returns true.
//      If the function fails, it returns false. For extended error information call "LGDspDll_GetLastError".
//
//   Required System Software:
//
//      2014/07/08 or newer.
//
extern "C" __declspec(dllimport) bool __cdecl LGDspDll_SetFaderButtons (int first_button, int count, const bool *value_array);



//
// LGDspDll_GetFaderButtons
// ========================
//
//   Description:
//
//      Gets the state of one or more consecutive fader buttons.
//      Each fader button can be either pressed (true) or released (false).
//      The Lasergraph DSP supports 64 fader buttons.
//
//   Parameters:
//
//      first_button         Number of the first fader button whose state is to be queried. 
//                           Allowed range: 0...63
//
//      count                Number of fader buttons whose states are to be queried.
//                           Allowed range: 1...64
//
//                           Note: All fader buttons to be queried have to be in the 0...63 range.
//
//      value_array          Pointer to an array where the fader button states are to be stored.
//
//   Return Value:
//
//      If the function succeeds, it returns true.
//      If the function fails, it returns false. For extended error information call "LGDspDll_GetLastError".
//
//   Required System Software:
//
//      2014/07/08 or newer.
//
extern "C" __declspec(dllimport) bool __cdecl LGDspDll_GetFaderButtons (int first_button, int count, bool *value_array);



//
// LGDspDll_SetSharedVars
// ======================
//
//   Description:
//
//      Sets one or more consecutive shared variables.
//      The Lasergraph DSP supports 64 shared variables.
//
//      Shared variables can be accessed by different Trickfilms and therefore
//      can be used to communicate between different DSPs.
//
//      Note: The current state of all shared variables can be displayed on
//            the Lasergraph DSP using the command "VARINFO".
//
//   Parameters:
//
//      first_var            Number of the first shared variable which is to be set. 
//                           Allowed range: 0...63
//
//      count                Number of shared variables which are to be set.
//                           Allowed range: 1...64
//
//                           Note: All shared variables to be set have to be in the 0...63 range.
//
//      value_array          Pointer to an array of values to which the shared variables are to be set.
//
//   Return Value:
//
//      If the function succeeds, it returns true.
//      If the function fails, it returns false. For extended error information call "LGDspDll_GetLastError".
//
//   Required System Software:
//
//      2014/05/15 or newer.
//
extern "C" __declspec(dllimport) bool __cdecl LGDspDll_SetSharedVars (int first_var, int count, const float *value_array);



//
// LGDspDll_GetSharedVars
// ======================
//
//   Description:
//
//      Gets one or more consecutive shared variables.
//      The Lasergraph DSP supports 64 shared variables.
//
//      Note: Shared variables can be accessed by different Trickfilms and 
//            therefore can be used to communicate between different DSPs.
//
//   Parameters:
//
//      first_var            Number of the first shared variable which is to be queried. 
//                           Allowed range: 0...63
//
//      count                Number of shared variables which are to be queried.
//                           Allowed range: 1...64
//
//                           Note: All shared variables queried have to be in the 0...63 range.
//
//      value_array          Pointer to an array where the shared variables are to be stored.
//
//   Return Value:
//
//      If the function succeeds, it returns true.
//      If the function fails, it returns false. For extended error information call "LGDspDll_GetLastError".
//
//   Required System Software:
//
//      2014/05/15 or newer.
//
extern "C" __declspec(dllimport) bool __cdecl LGDspDll_GetSharedVars (int first_var, int count, float *value_array);



//
// LGDspDll_SetDmxOut
// ==================
//
//   Description:
//
//      Sets one or more consecutive DMX output channels.
//      The Lasergraph DSP supports 256 DMX output channels.
//
//      Note: The function "LGDspDll_SetDmxOut" uses the Mapconfig of the Lasergraph DSP
//            to translate the specified virtual DMX channel numbers into physical numbers
//            which are actually used.
//
//   Parameters:
//
//      first_channel        Number of the first DMX output channel to be set. 
//                           Allowed range: 0...255
//
//      count                Number of DMX output channels which are to be set.
//                           Allowed range: 1...256
//
//                           Note: All DMX output channels to be set have to be in the 0...255 range.
//
//      value_array          Pointer to an array of values to which the DMX output channels are to be set.
//
//   Return Value:
//
//      If the function succeeds, it returns true.
//      If the function fails, it returns false. For extended error information call "LGDspDll_GetLastError".
//
//   Required System Software:
//
//      2014/11/12 or newer.
//
extern "C" __declspec(dllimport) bool __cdecl LGDspDll_SetDmxOut (int first_channel, int count, const unsigned char *value_array);



//
// LGDspDll_SetGlobalText
// ======================
//
//   Description:
//
//      Modifies a text in the "Global Text Table".
//
//      Each text in the "Global Text Table" is accessed using a path and a description.
//      The path is used to specify the directory where the altered texts will be saved.
//      If no directory is specified the directory "C:\System\GlobalTexts" is used.
//      The description is used to identify the different texts in the "Global Text Table".
//
//      Both, path and description, have to match the path and description entered in
//      the trickfilm command "DeFineText".
//
//      Note: The function "LGDspDll_SetGlobalText" cannot be used to add new items
//            in the "Global Text Table". It can only be used to modify existing ones.
// 
//   Parameters:
//
//      path                 Path where the altered text is to be stored.
//                           It has to be identical to the path entered in the command "DeFineText".
//
//      description          Description of the text to modify.
//                           It has to be identical to the description entered in the command "DeFineText".
//                           The description must not be empty.
//
//      font                 Name of the Lasergraph DSP font to be used (e.g. "2D_Alphabet").
//                           If no font is specified the previous one will be used.
//
//      text                 New text to be entered in the "Global Text Table".
//                           If text is empty the default text entered in the command "DeFineText" will be used.
//
//      save                 Specifies if the changes are to be stored on the hard disk drive.
//
//   Return Value:
//
//      If the function succeeds, it returns true.
//      If the function fails, it returns false. For extended error information call "LGDspDll_GetLastError".
//
//   Required System Software:
//
//      Available on all Mark 2.
//
extern "C" __declspec(dllimport) bool __cdecl LGDspDll_SetGlobalText (const char *path, const char *description, 
                                                          const char *font, const char *text, bool save = false);



//
// LGDspDll_GetEntries
// ===================
//
//   Description:
//
//      Determines which entries are available in the specified Trickfilm.
//
//      Note: The state of availability of an entry can only be queried if the Trickfilm is compiled!
//
//   Parameters:
//
//      film                 Number of the Trickfilm whose available entries are to be queried. 
//                           Allowed values:
//
//                              0  =>  Film 1
//                              1  =>  Film 2
//                              2  =>  Film 3
//                              3  =>  Film 4
//
//      entry_available      Points to the buffer where the state of the entries is stored:
//
//                              entry_available[0]:   true => Entry 0 is available  /  false => Entry 0 is not available
//                              entry_available[1]:   true => Entry 1 is available  /  false => Entry 1 is not available
//                                     ...
//
//      buffer_size          Specifies the size of the buffer and thereby the number of entries to be queried.
//
//   Return Value:
//
//      If the function succeeds, it returns true.
//      If the function fails, it returns false. For extended error information call "LGDspDll_GetLastError".
//
//   Required System Software:
//
//      2014/05/15 or newer.
//
extern "C" __declspec(dllimport) bool __cdecl LGDspDll_GetEntries (int film, bool *entry_available, int buffer_size);



//
// LGDspDll_GetEntryName
// =====================
//
//   Description:
//
//      Gets the name of the specified entry.
//      If the specified entry does not exist or has an empty description, an empty string is returned.
//
//      Note: Entry names can only be queried if the Trickfilm is compiled!
//
//   Parameters:
//
//      film                 Number of the Trickfilm where the entry whose name is to be queried is located. 
//                           Allowed values:
//
//                              0  =>  Film 1
//                              1  =>  Film 2
//                              2  =>  Film 3
//                              3  =>  Film 4
//
//      entry                Number of the entry whose name is to be queried.
//                           Allowed range: 0...999
//
//      entry_name           Pointer to the buffer that will receive the entry name.
//
//      max_count            Specifies the maximum number of characters to be copied to the buffer,
//                           including the NULL character.
//                           If the name of the entry is longer than the number of characters specified
//                           in max_count it will be truncated.
//
//   Return Value:
//
//      If the function succeeds, it returns true.
//      If the function fails, it returns false. For extended error information call "LGDspDll_GetLastError".
//
//   Required System Software:
//
//      2014/05/15 or newer.
//
extern "C" __declspec(dllimport) bool __cdecl LGDspDll_GetEntryName (int film, int entry, char *entry_name, int max_count);



//
// LGDspDll_GetAnimationNames
// ==========================
//
//   Description:
//
//      Determines the names of all loaded animations.
//      This function has to be called once before the animation names can be queried using
//      the function "LGDspDll_GetNextAnimationName".
//
//   Return Value:
//
//      If the function succeeds, it returns true.
//      If the function fails, it returns false. For extended error information call "LGDspDll_GetLastError".
//
//   Required System Software:
//
//      Available on all Mark 2.
//
extern "C" __declspec(dllimport) bool __cdecl LGDspDll_GetAnimationNames (void);



//
// LGDspDll_GetNextAnimationName
// =============================
//
//   Description:
//
//      Gets the name of the next loaded animation.
//      Before this function is called for the first time all available animation names
//      have to be determined using the function "LGDspDll_GetAnimationNames".
//
//   Parameters:
//
//      animation_name       Pointer to the buffer that will receive the animation name.
//
//      max_count            Specifies the maximum number of characters to be copied to the buffer,
//                           including the NULL character.
//                           If the name of the animation is longer than the number of characters
//                           specified in max_count it will be truncated.
//
//   Return Value:
//
//      The function returns true if an animation name has been copied into the specified buffer.
//      The function returns false if there is no more animation name available.
//
//   Required System Software:
//
//      Available on all Mark 2.
//
extern "C" __declspec(dllimport) bool __cdecl LGDspDll_GetNextAnimationName (char *animation_name, int max_count);



//
// LGDspDll_GetCatalogNames
// ========================
//
//   Description:
//
//      Determines the names of all loaded catalogs.
//      This function has to be called once before the catalog names can be queried using
//      the function "LGDspDll_GetNextCatalogName".
//
//   Return Value:
//
//      If the function succeeds, it returns true.
//      If the function fails, it returns false. For extended error information call "LGDspDll_GetLastError".
//
//   Required System Software:
//
//      Available on all Mark 2.
//
extern "C" __declspec(dllimport) bool __cdecl LGDspDll_GetCatalogNames (void);



//
// LGDspDll_GetNextCatalogName
// ===========================
//
//   Description:
//
//      Gets the name of the next loaded catalog.
//      Before this function is called for the first time all available catalog names
//      have to be determined using the function "LGDspDll_GetCatalogNames".
//
//   Parameters:
//
//      catalog_name         Pointer to the buffer that will receive the catalog name.
//
//      max_count            Specifies the maximum number of characters to be copied to the buffer,
//                           including the NULL character.
//                           If the name of the catalog is longer than the number of characters
//                           specified in max_count it will be truncated.
//
//   Return Value:
//
//      The function returns true if a catalog name has been copied into the specified buffer.
//      The function returns false if there is no more catalog name available.
//
//   Required System Software:
//
//      Available on all Mark 2.
//
extern "C" __declspec(dllimport) bool __cdecl LGDspDll_GetNextCatalogName (char *catalog_name, int max_count);



//
// LGDspDll_GetPictureNames
// ========================
//
//   Description:
//
//      Determines the names of all loaded pictures within the specified catalog.
//      This function has to be called once before the picture names can be queried using
//      the function "LGDspDll_GetNextPictureName".
//
//   Parameter:
//
//      catalog_name         Name of the catalog containing the pictures whose names are
//                           to be queried.
//
//   Return Value:
//
//      If the function succeeds, it returns true.
//      If the function fails, it returns false. For extended error information call "LGDspDll_GetLastError".
//
//   Required System Software:
//
//      Available on all Mark 2.
//
extern "C" __declspec(dllimport) bool __cdecl LGDspDll_GetPictureNames (const char *catalog_name);



//
// LGDspDll_GetNextPictureName
// ===========================
//
//   Description:
//
//      Gets the name of the next loaded picture.
//      Before this function is called for the first time all available picture names
//      have to be determined using the function "LGDspDll_GetPictureNames".
//
//   Parameters:
//
//      picture_name         Pointer to the buffer that will receive the picture name.
//
//      max_count            Specifies the maximum number of characters to be copied to the buffer,
//                           including the NULL character.
//                           If the name of the picture is longer than the number of characters
//                           specified in max_count it will be truncated.
//
//   Return Value:
//
//      The function returns true if a picture name has been copied into the specified buffer.
//      The function returns false if there is no more picture name available.
//
//   Required System Software:
//
//      Available on all Mark 2.
//
extern "C" __declspec(dllimport) bool __cdecl LGDspDll_GetNextPictureName (char *picture_name, int max_count);



//
// LGDspDll_Goto
// =============
//
//   Description:
//
//      Starts an entry in the specified Trickfilm.
//      If the Trickfilm is already running it will branch to the desired entry.
//      If the Trickfilm is not running it will be started at the desired entry.
//
//   Parameters:
//
//      film                 Number of the Trickfilm where the entry is to be started. 
//                           Allowed values:
//
//                             -1  =>  Currently selected Trickfilm
//
//                              0  =>  Film 1
//                              1  =>  Film 2
//                              2  =>  Film 3
//                              3  =>  Film 4
//
//      entry                Number of the entry to be started.
//                           Allowed range: 0...999
//
//   Return Value:
//
//      If the function succeeds, it returns true.
//      If the function fails, it returns false. For extended error information call "LGDspDll_GetLastError".
//
//   Required System Software:
//
//      2014/05/15 or newer.
//
extern "C" __declspec(dllimport) bool __cdecl LGDspDll_Goto (int film, int entry);



//
// LGDspDll_ExeCmd
// ===============
//
//   Description:
//
//      Enters the specified command into the command line of the Lasergraph DSP and
//      executes it as if it was entered locally.
//
//   Parameter:
//
//      command              Command to be executed.
//
//   Return Value:
//
//      If the function succeeds, it returns true.
//      If the function fails, it returns false. For extended error information call "LGDspDll_GetLastError".
//
//   Required System Software:
//
//      Available on all Mark 2.
//
extern "C" __declspec(dllimport) bool __cdecl LGDspDll_ExeCmd (const char *command);







// ----------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------



//
// Definition of a single point within a picture
//
class DspPoint
{
public:

    enum
    {
        MATRIX_MASK  = 0xe000,
        REPEATS_MASK = 0x1e00,
        ENDFLAG_MASK = 0x0100,
        VECTOR_MASK  = 0x0080,   // <- low active, see below!
        BLANK_MASK   = 0x0040,
        COLOR_MASK   = 0x003f
    };


    DspPoint ()  
    {
        m_x          = 0;
        m_y          = 0;
        m_z          = 0;
        m_attributes = BLANK_MASK | VECTOR_MASK;
    }

    DspPoint (short x, short y, short z, int color, int repeats, int matrix, bool blank, bool vector, bool endflag)
    {
        m_x          = x;
        m_y          = y;
        m_z          = z;
        m_attributes = (unsigned short)(   ((color   <<  0) & COLOR_MASK)
                                         | ((repeats <<  9) & REPEATS_MASK)
                                         | ((matrix  << 13) & MATRIX_MASK)
                                         | ((blank        ) ? BLANK_MASK   : 0x0000)
                                         | ((vector       ) ? 0x0000       : VECTOR_MASK)
                                         | ((endflag      ) ? ENDFLAG_MASK : 0x0000));
    }


    void           SetX          (short x)       { m_x = x; }
    void           SetY          (short y)       { m_y = y; }
    void           SetZ          (short z)       { m_z = z; }
    void           SetColor      (int color)     { m_attributes = (unsigned short)((m_attributes & ~COLOR_MASK)   | ((color   <<  0) & COLOR_MASK));   }
    void           SetRepeats    (int repeats)   { m_attributes = (unsigned short)((m_attributes & ~REPEATS_MASK) | ((repeats <<  9) & REPEATS_MASK)); }
    void           SetMatrix     (int matrix)    { m_attributes = (unsigned short)((m_attributes & ~MATRIX_MASK)  | ((matrix  << 13) & MATRIX_MASK));  }
    void           SetBlank      (bool blank)    { if (blank)    m_attributes |=  BLANK_MASK;    else  m_attributes &= ~BLANK_MASK;   }
    void           SetVector     (bool vector)   { if (vector)   m_attributes &= ~VECTOR_MASK;   else  m_attributes |=  VECTOR_MASK;  }
    void           SetEndflag    (bool endflag)  { if (endflag)  m_attributes |=  ENDFLAG_MASK;  else  m_attributes &= ~ENDFLAG_MASK; }

    short          GetX          ()  const  { return (m_x);          }
    short          GetY          ()  const  { return (m_y);          }
    short          GetZ          ()  const  { return (m_z);          }
    unsigned short GetAttributes ()  const  { return (m_attributes); }


private:

    unsigned short m_attributes;  // %mmmrrrrevbcccccc
                                  //
                                  //    mmm      Matrix (0-7)
                                  //
                                  //    rrrr     Number of repeats (0-15)
                                  //
                                  //    e        Endflag   0 = this is not the last point of the picture
                                  //                       1 = this is the last point of the picture
                                  //
                                  //    v        Vector    0 = this point and the following point define a vector
                                  //                       1 = this is not the beginning of a vector
                                  //
                                  //    b        Blanking  0 = the following line is visible
                                  //                       1 = the following line is invisible
                                  //
                                  //    cccccc   Color index for the following line (0-63)

    short          m_x;           // X coordinate         -32768 = leftmost  
                                  //                           0 = center
                                  //                      +32767 = rightmost

    short          m_y;           // Y coordinate         -32768 = bottommost 
                                  //                           0 = center
                                  //                      +32767 = topmost

    short          m_z;           // Z coordinate         -32768 = closest
                                  //                           0 = center
                                  //                      +32767 = farthest
};



//
// Definition of a single point within a true color picture
//
class DspPointRGB : public DspPoint
{
public:

    DspPointRGB () : DspPoint ()
    {
        m_red   = 0;
        m_green = 0;
        m_blue  = 0;
    }

    DspPointRGB (short x, short y, short z,
                 unsigned char red, unsigned char green, unsigned char blue,
                 int repeats, int matrix, bool blank, bool vector, bool endflag) :
        DspPoint (x, y, z, /*color*/ 0, repeats, matrix, blank, vector, endflag)
    {
        m_red   = red;
        m_green = green;
        m_blue  = blue;
    }


    void           SetRed   (unsigned char red)    { m_red   = red;   }
    void           SetGreen (unsigned char green)  { m_green = green; }
    void           SetBlue  (unsigned char blue)   { m_blue  = blue;  }
                 
    unsigned char  GetRed   ()  const  { return (m_red);   }
    unsigned char  GetGreen ()  const  { return (m_green); }
    unsigned char  GetBlue  ()  const  { return (m_blue);  }
                 
                 
private:         
                 
    unsigned char  m_red;         // red component of color       0 = zero intensity
                                  //                            255 = maximum intensity

    unsigned char  m_green;       // green component of color     0 = zero intensity
                                  //                            255 = maximum intensity

    unsigned char  m_blue;        // blue component of color      0 = zero intensity
                                  //                            255 = maximum intensity
};





