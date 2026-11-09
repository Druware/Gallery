/*
 * Haiku Gallery - message constants.
 *
 * Every BMessage 'what' code used by the application lives here so that
 * codes stay unique. Pages never share codes: the main window forwards
 * unknown messages to the pages and the first page that recognises a
 * code consumes it.
 */
#ifndef MESSAGES_H
#define MESSAGES_H

#include <SupportDefs.h>


// Main window
const uint32 MSG_NAV_SELECTED			= 'nvsl';
const uint32 MSG_SEARCH_CHANGED			= 'srch';
const uint32 MSG_SHOW_PAGE				= 'shpg';	// int32 "index"
const uint32 MSG_GO_HOME				= 'home';
const uint32 MSG_TOGGLE_NAV				= 'tgnv';
const uint32 MSG_FOCUS_SEARCH			= 'fcsr';
const uint32 MSG_OPEN_DOCS				= 'opdc';
const uint32 MSG_OPEN_BOOK				= 'opbk';

// Shared page chrome (handled by GalleryPage itself)
const uint32 MSG_COPY_SOURCE			= 'cpsr';

// BButton page
const uint32 MSG_BTN_CLICKED			= 'btcl';
const uint32 MSG_BTN_TOGGLED			= 'bttg';
const uint32 MSG_BTN_ENABLED			= 'bten';
const uint32 MSG_BTN_LABEL				= 'btlb';

// BCheckBox page
const uint32 MSG_CB_ALL					= 'cbal';
const uint32 MSG_CB_ITEM				= 'cbit';
const uint32 MSG_CB_ENABLED				= 'cben';

// BRadioButton page
const uint32 MSG_RB_CHOSEN				= 'rbch';	// int32 "index"
const uint32 MSG_RB_ENABLED				= 'rben';

// BSlider page
const uint32 MSG_SL_CHANGED				= 'slch';
const uint32 MSG_SL_MODIFIED			= 'slmd';
const uint32 MSG_SL_VERTICAL			= 'slvt';
const uint32 MSG_SL_HASHMARKS			= 'slhm';
const uint32 MSG_SL_TRIANGLE			= 'sltr';
const uint32 MSG_SL_FILL				= 'slfl';
const uint32 MSG_SL_ENABLED				= 'slen';

// BColorControl page
const uint32 MSG_CC_CHANGED				= 'ccch';
const uint32 MSG_CC_LAYOUT				= 'ccly';
const uint32 MSG_CC_CELLSIZE			= 'cccs';
const uint32 MSG_CC_ENABLED				= 'ccen';

// BFilePanel page
const uint32 MSG_FP_SHOW_OPEN			= 'fpso';
const uint32 MSG_FP_SHOW_SAVE			= 'fpss';
const uint32 MSG_FP_OPENED				= 'fpop';
const uint32 MSG_FP_SAVED				= 'fpsv';

// BStringView page
const uint32 MSG_SV_TEXT				= 'svtx';
const uint32 MSG_SV_ALIGN				= 'sval';
const uint32 MSG_SV_TRUNCATE			= 'svtr';
const uint32 MSG_SV_BOLD				= 'svbd';

// BTextControl page
const uint32 MSG_TC_MODIFIED			= 'tcmd';
const uint32 MSG_TC_INVOKED				= 'tciv';
const uint32 MSG_TC_ENABLED				= 'tcen';
const uint32 MSG_TC_INVALID				= 'tcin';
const uint32 MSG_TC_PASSWORD			= 'tcpw';

// BTextView page
const uint32 MSG_TV_CHANGED				= 'tvch';
const uint32 MSG_TV_EDITABLE			= 'tved';
const uint32 MSG_TV_SELECTABLE			= 'tvsl';
const uint32 MSG_TV_WORDWRAP			= 'tvww';

// BListView page
const uint32 MSG_LV_SELECTED			= 'lvsl';
const uint32 MSG_LV_INVOKED				= 'lviv';
const uint32 MSG_LV_MULTIPLE			= 'lvmu';
const uint32 MSG_LV_ADD					= 'lvad';
const uint32 MSG_LV_REMOVE				= 'lvrm';

// BOutlineListView page
const uint32 MSG_OL_SELECTED			= 'olsl';
const uint32 MSG_OL_EXPAND_ALL			= 'olex';
const uint32 MSG_OL_COLLAPSE_ALL		= 'olco';
const uint32 MSG_OL_ADD_CHILD			= 'olad';

// BMenuBar page
const uint32 MSG_MB_ITEM				= 'mbit';	// string "label"
const uint32 MSG_MB_EDIT_ENABLED		= 'mben';

// BPopUpMenu page
const uint32 MSG_PM_PICKED				= 'pmpk';	// string "label"
const uint32 MSG_PM_DISABLED_ITEM		= 'pmdi';

// BMenuField page
const uint32 MSG_MF_SELECTED			= 'mfsl';	// string "label"
const uint32 MSG_MF_ENABLED				= 'mfen';
const uint32 MSG_MF_LABEL				= 'mflb';

// BOptionPopUp page
const uint32 MSG_OP_CHANGED				= 'opch';
const uint32 MSG_OP_ENABLED				= 'open';
const uint32 MSG_OP_ADD					= 'opad';

// BStatusBar page
const uint32 MSG_SB_STEP				= 'sbst';
const uint32 MSG_SB_RESET				= 'sbrs';
const uint32 MSG_SB_ANIMATE				= 'sban';
const uint32 MSG_SB_TICK				= 'sbtk';
const uint32 MSG_SB_COLOR				= 'sbcl';

// BAlert page
const uint32 MSG_AL_SHOW				= 'alsh';
const uint32 MSG_AL_RESULT				= 'alrs';	// int32 "which"
const uint32 MSG_AL_TYPE				= 'alty';
const uint32 MSG_AL_BUTTONS				= 'albt';

// Tooltips page
const uint32 MSG_TT_TEXT				= 'tttx';
const uint32 MSG_TT_ENABLED				= 'tten';

// BGroupLayout page
const uint32 MSG_GL_VERTICAL			= 'glvt';
const uint32 MSG_GL_SPACING				= 'glsp';
const uint32 MSG_GL_INSETS				= 'glin';
const uint32 MSG_GL_WEIGHTS				= 'glwt';

// BGridLayout page
const uint32 MSG_GR_HSPACING			= 'grhs';
const uint32 MSG_GR_VSPACING			= 'grvs';
const uint32 MSG_GR_WEIGHT				= 'grwt';

// BSplitView page
const uint32 MSG_SP_VERTICAL			= 'spvt';
const uint32 MSG_SP_COLLAPSE			= 'spco';
const uint32 MSG_SP_SPLITTER			= 'spss';

// BCardLayout page
const uint32 MSG_CL_PREVIOUS			= 'clpr';
const uint32 MSG_CL_NEXT				= 'clnx';
const uint32 MSG_CL_PICK				= 'clpk';

// BTabView page
const uint32 MSG_TB_SELECTED			= 'tbsl';	// int32 "index"
const uint32 MSG_TB_SIDE				= 'tbsd';
const uint32 MSG_TB_BORDER				= 'tbbd';

// BBox page
const uint32 MSG_BX_BORDER				= 'bxbd';
const uint32 MSG_BX_LABEL				= 'bxlb';
const uint32 MSG_BX_VIEW_LABEL			= 'bxvl';
const uint32 MSG_BX_LABEL_CHECK			= 'bxlc';

// BScrollView page
const uint32 MSG_SC_BORDER				= 'scbd';
const uint32 MSG_SC_HIGHLIGHT			= 'schl';

// BSeparatorView page
const uint32 MSG_SE_LABEL				= 'selb';
const uint32 MSG_SE_BORDER				= 'sebd';
const uint32 MSG_SE_ALIGN				= 'seal';

#endif	// MESSAGES_H
