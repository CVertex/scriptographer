/*
 * Scriptographer
 *
 * This file is part of Scriptographer, a Plugin for Adobe Illustrator.
 *
 * Copyright (c) 2002-2008 Juerg Lehni, http://www.scratchdisk.com.
 * All rights reserved.
 *
 * Please visit http://scriptographer.com/ for updates and contact.
 *
 * -- GPL LICENSE NOTICE --
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 * -- GPL LICENSE NOTICE --
 *
 * $Id$
 */

#include "jniMacros.h"
#include "exceptions.h"

class ScriptographerEngine {
private:
    JavaVM* m_javaVM;
	char *m_homeDir;
	bool m_initialized;
	Array<AIDocumentHandle> m_suspendedDocuments;

#ifdef MAC_ENV
	// used for the javaThread workaround:
	MPQueueID m_requestQueue;
	MPQueueID m_responseQueue;
#endif

public:
	AIDictKey m_artHandleKey;
	AIDictKey m_docReflowKey;

	/*
	 * Opaque JVM handles to Java classes, methods and objects required for
	 * Java reflection.  These are computed and cached during initialization.
	 */
// JSE:
	jclass cls_Object;
	jmethodID mid_Object_toString;

	jclass cls_System;
	jfieldID fid_System_out;
	
	jclass cls_PrintStream;
	jmethodID mid_PrintStream_println;

	jclass cls_Class;
	jmethodID mid_Class_getName;
	jmethodID mid_Class_getConstructors;

	jclass cls_String;
	jmethodID cid_String;
	jmethodID mid_String_getBytes;
	
	jclass cls_Number;
	jmethodID mid_Number_intValue;
	jmethodID mid_Number_floatValue;
	
	jclass cls_Integer;
	jmethodID cid_Integer;
	
	jclass cls_Float;
	jmethodID cid_Float;
	
	jclass cls_Boolean;
	jmethodID cid_Boolean;
	jmethodID mid_Boolean_booleanValue;
	
	jclass cls_File;
	jmethodID cid_File;
	jmethodID mid_File_getPath;
	
	jclass cls_Collection;
	jmethodID mid_Collection_add;

	jclass cls_Map;
	jmethodID mid_Map_keySet;
	jmethodID mid_Map_put;
	jmethodID mid_Map_get;
	
	jclass cls_HashMap;
	jmethodID cid_HashMap;
	
	jclass cls_ArrayList;
	jmethodID cid_ArrayList;
	
	jclass cls_Set;
	jmethodID mid_Set_iterator;
	
	jclass cls_Iterator;
	jmethodID mid_Iterator_hasNext;
	jmethodID mid_Iterator_next;
	jmethodID mid_Iterator_remove;

	jclass cls_OutOfMemoryError;
	
	jclass cls_awt_Color;
	jmethodID cid_awt_Color;
	jmethodID mid_awt_Color_getColorComponents;
	
	jclass cls_awt_ICC_Profile;
	jmethodID mid_awt_ICC_Profile_getInstance;
	
// Loader:
	jclass cls_Loader;
	jmethodID mid_Loader_init;
	jmethodID mid_Loader_reload;
	jmethodID mid_Loader_loadClass;

// Scratchdisk:
	jclass cls_IntMap;
	jmethodID cid_IntMap;
	jmethodID mid_IntMap_put;
	
	jclass cls_List;
	jmethodID mid_List_size;
	jmethodID mid_List_get;
	
// Scriptographer:
	jclass cls_ScriptographerEngine;
	jmethodID mid_ScriptographerEngine_init;
	jmethodID mid_ScriptographerEngine_destroy;
	jmethodID mid_ScriptographerEngine_reportError;
	jmethodID mid_ScriptographerEngine_onHandleEvent;

	jclass cls_ScriptographerException;

	jclass cls_CommitManager;
	jmethodID mid_CommitManager_commit;

// AI:
	jclass cls_ai_NativeObject;
	jfieldID fid_ai_NativeObject_handle;

	jclass cls_ai_DocumentObject;
	jfieldID fid_ai_DocumentObject_document;
	
	jclass cls_ai_Dictionary;
	jfieldID fid_ai_Dictionary_handle;
	jmethodID mid_ai_Dictionary_wrapHandle;

	jclass cls_ai_Tool;
	jmethodID cid_ai_Tool;
	jmethodID mid_ai_Tool_onHandleEvent;

	jclass cls_ai_Point;
	jmethodID cid_ai_Point;
	jfieldID fid_ai_Point_x;
	jfieldID fid_ai_Point_y;
	jmethodID mid_ai_Point_set;

	jclass cls_ai_Rectangle;
	jmethodID cid_ai_Rectangle;
	jfieldID fid_ai_Rectangle_x;
	jfieldID fid_ai_Rectangle_y;
	jfieldID fid_ai_Rectangle_width;
	jfieldID fid_ai_Rectangle_height;
	jmethodID mid_ai_Rectangle_set;

	jclass cls_ai_Size;
	jmethodID cid_ai_Size;
	jfieldID fid_ai_Size_width;
	jfieldID fid_ai_Size_height;
	jmethodID mid_ai_Size_set;
	
	jclass cls_ai_Matrix;
	jmethodID cid_ai_Matrix;
	jmethodID mid_ai_Matrix_getScaleX;
	jmethodID mid_ai_Matrix_getShearY;
	jmethodID mid_ai_Matrix_getShearX;
	jmethodID mid_ai_Matrix_getScaleY;
	jmethodID mid_ai_Matrix_getTranslateX;
	jmethodID mid_ai_Matrix_getTranslateY;
	
	jclass cls_ai_Color;
	jmethodID mid_ai_Color_getComponents;
	jobject obj_ai_Color_NONE;

	jclass cls_ai_GrayColor;
	jmethodID cid_ai_GrayColor;
	
	jclass cls_ai_RGBColor;
	jmethodID cid_ai_RGBColor;
	
	jclass cls_ai_CMYKColor;
	jmethodID cid_ai_CMYKColor;
	
	jclass cls_ai_GradientColor;
	jmethodID cid_ai_GradientColor;
	jmethodID mid_ai_GradientColor_set;
	
	jclass cls_ai_PatternColor;
	jmethodID cid_ai_PatternColor;
	jmethodID mid_ai_PatternColor_set;
	
	jclass cls_ai_Item;
	jfieldID fid_ai_Item_version;
	jfieldID fid_ai_Item_dictionaryHandle;
	jmethodID mid_ai_Item_wrapHandle;
	jmethodID mid_ai_Item_getIfWrapped;
	jmethodID mid_ai_Item_updateIfWrapped;
	jmethodID mid_ai_Item_changeHandle;
	jmethodID mid_ai_Item_commit;
	
	jclass cls_ai_ItemSet;
	jmethodID cid_ItemSet;
	jmethodID mid_ai_ItemSet_add;

	jclass cls_ai_Path;
	jclass cls_ai_CompoundPath;
	jclass cls_ai_TextItem;
	
	jclass cls_ai_TextRange;
	jmethodID cid_ai_TextRange;
	jfieldID fid_ai_TextRange_glyphRuns;

	jclass cls_ai_TextStory;
	
	jclass cls_ai_PathStyle;
	jmethodID mid_PathStyle_init;
	
	jclass cls_ai_FillStyle;
	jmethodID cid_ai_FillStyle;
	jmethodID mid_ai_FillStyle_init;
	jmethodID mid_ai_FillStyle_initNative;
	
	jclass cls_ai_StrokeStyle;
	jmethodID cid_ai_StrokeStyle;
	jmethodID mid_ai_StrokeStyle_init;
	jmethodID mid_ai_StrokeStyle_initNative;
	
	jclass cls_ai_CharacterStyle;
	jmethodID mid_ai_CharacterStyle_markSetStyle;

	jclass cls_ai_ParagraphStyle;
	jmethodID mid_ai_ParagraphStyle_markSetStyle;
	
	jclass cls_ai_Group;
	
	jclass cls_ai_Raster;
	jfieldID fid_ai_Raster_data;
	
	jclass cls_ai_PlacedFile;

	jclass cls_ai_PlacedSymbol;

	jclass cls_ai_Tracing;
	jmethodID mid_ai_Tracing_markDirty;
	
	jclass cls_ai_Layer;
	
	jclass cls_ai_Segment;
	jclass cls_ai_Curve;
	
	jclass cls_ai_TabletValue;
	jmethodID cid_ai_TabletValue;
	jfieldID fid_ai_TabletValue_offset;
	jfieldID fid_ai_TabletValue_value;

	jclass cls_ai_GradientStop;
	jmethodID mid_ai_GradientStop_set;
	
	jclass cls_ai_Document;
	
	jclass cls_ai_LiveEffect;
	jmethodID cid_ai_LiveEffect;
	jmethodID mid_ai_LiveEffect_onEditParameters;
	jmethodID mid_ai_LiveEffect_onCalculate;
	jmethodID mid_ai_LiveEffect_onInterpolate;
	jmethodID mid_ai_LiveEffect_onGetInputType;
	
	jclass cls_sg_Timer;
	jmethodID cid_sg_Timer;
	jmethodID mid_sg_Timer_onExecute;
	
	jclass cls_ai_Annotator;
	jmethodID cid_ai_Annotator;
	jmethodID mid_ai_Annotator_onDraw;
	jmethodID mid_ai_Annotator_onInvalidate;
	
	jclass cls_ai_HitTest;
	jmethodID cid_ai_HitTest;
	
	jclass cls_ai_FileFormat;
	jmethodID cid_ai_FileFormat;
// ADM:
	jclass cls_adm_NativeObject;
	jfieldID fid_adm_NativeObject_handle;

	jclass cls_adm_Rectangle;
	jmethodID cid_adm_Rectangle;
	jfieldID fid_adm_Rectangle_x;
	jfieldID fid_adm_Rectangle_y;
	jfieldID fid_adm_Rectangle_width;
	jfieldID fid_adm_Rectangle_height;
	jmethodID mid_adm_Rectangle_set;
	
	jclass cls_adm_Point;
	jmethodID cid_adm_Point;
	jfieldID fid_adm_Point_x;
	jfieldID fid_adm_Point_y;
	jmethodID mid_adm_Point_set;
	
	jclass cls_adm_Size;
	jmethodID cid_adm_Size;
	jfieldID fid_adm_Size_width;
	jfieldID fid_adm_Size_height;
	jmethodID mid_adm_Size_set;

	jclass cls_adm_Dialog;
	jmethodID mid_adm_Dialog_onSizeChanged;

	jclass cls_adm_PopupDialog;

	jclass cls_adm_DialogGroupInfo;
	jmethodID cid_adm_DialogGroupInfo;
	
	jclass cls_adm_Drawer;
	jmethodID cid_adm_Drawer;

	jclass cls_adm_FontInfo;
	jmethodID cid_adm_FontInfo;
	
	jclass cls_adm_Image;
	jfieldID fid_adm_Image_byteWidth;
	jfieldID fid_adm_Image_bitsPerPixel;
	jmethodID mid_adm_Image_getIconHandle;

	jclass cls_adm_ListItem;
	jfieldID fid_adm_ListItem_listHandle;

	jclass cls_adm_HierarchyList;
	
	jclass cls_adm_ListEntry;
	
	jclass cls_adm_HierarchyListEntry;

	jclass cls_adm_NotificationHandler;
	jfieldID fid_adm_NotificationHandler_tracker;
	jfieldID fid_adm_NotificationHandler_drawer;
	jmethodID mid_adm_NotificationHandler_onNotify;
	jmethodID mid_adm_NotificationHandler_onDraw;
		
	jclass cls_adm_Tracker;
	jmethodID mid_adm_Tracker_onTrack;
	
	jclass cls_adm_MenuItem;
	jmethodID mid_adm_MenuItem_wrapHandle;
	jmethodID mid_adm_MenuItem_onSelect;
	jmethodID mid_adm_MenuItem_onUpdate;
	
	jclass cls_adm_MenuGroup;
	
public:
	ScriptographerEngine(const char *homeDir);
	~ScriptographerEngine();
	
	void init();
	void exit();

#ifdef MAC_ENV
	void javaThread();
#endif

	void initReflection(JNIEnv *env);
	// registerNatives code is automatically generated by jni.js / build.xm in registerNatives.cpp:
	void registerNatives(JNIEnv *env);
	void registerClassNatives(JNIEnv *env, const char *className, const JNINativeMethod *methods, int count);

	void initEngine();
	jstring reloadEngine();
	
	bool isInitialized() {
		return m_initialized;
	}

	long getNanoTime();
	bool isKeyDown(short keycode);
	
	void println(JNIEnv *env, const char *str, ...);
	void reportError(JNIEnv *env);

	// java.lang.Boolean <-> jboolean
	jobject convertBoolean(JNIEnv *env, jboolean value);	
	jboolean convertBoolean(JNIEnv *env, jobject value);

	// java.lang.Integer <-> jint
	jobject convertInteger(JNIEnv *env, jint value);
	jint convertInteger(JNIEnv *env, jobject value);

	// java.lang.Float <-> jfloat
	jobject convertFloat(JNIEnv *env, jfloat value);
	jfloat convertFloat(JNIEnv *env, jobject value);
	
	// com.scriptographer.awt.Point <-> AIRealPoint
	jobject convertPoint(JNIEnv *env, AIReal x, AIReal y, jobject res = NULL);	
	jobject convertPoint(JNIEnv *env, AIRealPoint *pt, jobject res = NULL) {
		return convertPoint(env, pt->h, pt->v, res);
	}
	AIRealPoint *convertPoint(JNIEnv *env, jobject pt, AIRealPoint *res = NULL);

	// com.scriptographer.adm.Point <-> ADMPoint
	jobject convertPoint(JNIEnv *env, int x, int y, jobject res = NULL);
	jobject convertPoint(JNIEnv *env, ADMPoint *pt, jobject res = NULL) {
		return convertPoint(env, pt->h, pt->v, res);
	}
	ADMPoint *convertPoint(JNIEnv *env, jobject pt, ADMPoint *res = NULL);

	// com.scriptographer.ai.Rectangle <-> AIRealRect
	jobject convertRectangle(JNIEnv *env, AIReal left, AIReal top, AIReal right, AIReal bottom, jobject res = NULL);
	jobject convertRectangle(JNIEnv *env, AIRealRect *rt, jobject res = NULL) {
		return convertRectangle(env, rt->left, rt->top, rt->right, rt->bottom, res);
	}
	AIRealRect *convertRectangle(JNIEnv *env, jobject rt, AIRealRect *res = NULL);	

	// java.awt.Rectangle <-> ADMRect
	jobject convertRectangle(JNIEnv *env, int left, int top, int right, int bottom, jobject res = NULL);
	jobject convertRectangle(JNIEnv *env, ADMRect *rt, jobject res = NULL) {
		return convertRectangle(env, rt->left, rt->top, rt->right, rt->bottom, res);
	}
	ADMRect *convertRectangle(JNIEnv *env, jobject rt, ADMRect *res = NULL);	

	// com.scriptographer.ai.Size <-> AIRealPoint
	jobject convertSize(JNIEnv *env, float width, float height, jobject res = NULL);
	jobject convertSize(JNIEnv *env, AIRealPoint *size, jobject res = NULL) {
		return convertSize(env, size->h, size->v, res);
	}
	AIRealPoint *convertSize(JNIEnv *env, jobject size, AIRealPoint *res = NULL);

	// com.scriptographer.adm.Size <-> ADMPoint
	jobject convertSize(JNIEnv *env, int width, int height, jobject res = NULL);
	jobject convertSize(JNIEnv *env, ADMPoint *size, jobject res = NULL) {
		return convertSize(env, size->h, size->v, res);
	}
	ADMPoint *convertSize(JNIEnv *env, jobject size, ADMPoint *res = NULL);

	// java.awt.Color <-> ADMRGBColor
	jobject convertColor(JNIEnv *env, ADMRGBColor *srcCol);	
	ADMRGBColor *convertColor(JNIEnv *env, jobject srcCol, ADMRGBColor *dstCol = NULL);	

	// com.scriptoggrapher.ai.Color <-> AIColor
	jobject convertColor(JNIEnv *env, AIColor *srcCol, AIReal alpha = 1.0f);
	AIColor *convertColor(JNIEnv *env, jobject srcCol, AIColor *dstCol = NULL, AIReal *alpha = NULL);	
	AIColor *convertColor(JNIEnv *env, jfloatArray srcCol, AIColor *dstCol = NULL, AIReal *alpha = NULL);

	// AIColor <-> ADMRGBColor
	AIColor *convertColor(ADMRGBColor *srcCol, AIColor *dstCol = NULL);	
	ADMRGBColor *convertColor(AIColor *srcCol, ADMRGBColor *dstCol = NULL);	

	// AIColor <-> AIColor
	AIColor *convertColor(AIColor *srcCol, AIColorConversionSpaceValue dstSpace, AIColor *dstCol = NULL, AIReal srcAlpha = 1.0f, AIReal *dstAlpha = NULL);

	// com.scriptoggrapher.ai.Matrix <-> AIRealMatrix
	jobject convertMatrix(JNIEnv *env, AIRealMatrix *mt, jobject res = NULL);
	AIRealMatrix *convertMatrix(JNIEnv *env, jobject mt, AIRealMatrix *res = NULL);

	// com.scriptoggrapher.ai.FillStyle <-> AIFillStyle
	jobject convertFillStyle(JNIEnv *env, AIFillStyle *style, jobject res = NULL);
	AIFillStyle *convertFillStyle(JNIEnv *env, jobject style, AIFillStyle *res = NULL);

	// com.scriptoggrapher.ai.StrokeStyle <-> AIStrokeStyle
	jobject convertStrokeStyle(JNIEnv *env, AIStrokeStyle *style, jobject res = NULL);
	AIStrokeStyle *convertStrokeStyle(JNIEnv *env, jobject style, AIStrokeStyle *res = NULL);

	// com.scriptoggrapher.ai.ItemSet <-> AIArtSet
	jobject convertArtSet(JNIEnv *env, AIArtSet set, bool layerOnly = false);
	AIArtSet convertArtSet(JNIEnv *env, jobject itemSet);

	// java.io.File <-> SPPlatformFileSpecification
	char *getFilePath(JNIEnv *env, jobject file);
	jobject convertFile(JNIEnv *env, SPPlatformFileSpecification *fileSpec);
	SPPlatformFileSpecification *convertFile(JNIEnv *env, jobject file, SPPlatformFileSpecification *res = NULL);
	
	// AI Handles
	int getAIObjectHandle(JNIEnv *env, jobject obj, const char *name);
	int getDocumentObjectHandle(JNIEnv *env, jobject obj, bool activateDoc, const char *name);

	AIArtHandle getArtHandle(JNIEnv *env, jobject obj, bool activateDoc = false, AIDocumentHandle *doc = NULL);
	AILayerHandle getLayerHandle(JNIEnv *env, jobject obj, bool activateDoc = false);
	AIDocumentHandle getDocumentHandle(JNIEnv *env, jobject obj, bool activateDoc = false);
	AIDictionaryRef getArtDictionaryHandle(JNIEnv *env, jobject obj);

	inline AIPatternHandle getPatternHandle(JNIEnv *env, jobject obj, bool activateDoc = false) {
		return (AIPatternHandle) getDocumentObjectHandle(env, obj, activateDoc, "pattern");
	}
	
	inline AISwatchRef getSwatchHandle(JNIEnv *env, jobject obj, bool activateDoc = false) {
		return (AISwatchRef) getDocumentObjectHandle(env, obj, activateDoc, "swatch");
	}
	
	inline AIGradientHandle getGradientHandle(JNIEnv *env, jobject obj, bool activateDoc = false) {
		return (AIGradientHandle) getDocumentObjectHandle(env, obj, activateDoc, "gradient");
	}

	inline AIDocumentViewHandle getDocumentViewHandle(JNIEnv *env, jobject obj, bool activateDoc = false) {
		return (AIDocumentViewHandle) getDocumentObjectHandle(env, obj, activateDoc, "view");
	}
	
	inline AIFontKey getFontHandle(JNIEnv *env, jobject obj) {
		return (AIFontKey) getAIObjectHandle(env, obj, "font");
	}

	inline AIDictionaryRef getDictionaryHandle(JNIEnv *env, jobject obj) {
		return (AIDictionaryRef) getAIObjectHandle(env, obj, "dictionary");
	}

	inline AIToolHandle getToolHandle(JNIEnv *env, jobject obj) {
		return (AIToolHandle) getAIObjectHandle(env, obj, "tool");
	}

	inline AILiveEffectHandle getLiveEffectHandle(JNIEnv *env, jobject obj) {
		return (AILiveEffectHandle) getAIObjectHandle(env, obj, "effect");
	}

	// ATE Handles
	ATE::TextFrameRef getTextFrameHandle(JNIEnv *env, jobject obj, bool activateDoc = false);

	inline ATE::TextRangeRef getTextRangeHandle(JNIEnv *env, jobject obj, bool activateDoc = false) {
		return (ATE::TextRangeRef) getDocumentObjectHandle(env, obj, activateDoc, "text range");
	}
	
	inline ATE::StoryRef getStoryHandle(JNIEnv *env, jobject obj, bool activateDoc = false) {
		return (ATE::StoryRef) getDocumentObjectHandle(env, obj, activateDoc, "text story");
	}
	
	inline ATE::CharFeaturesRef getCharFeaturesHandle(JNIEnv *env, jobject obj) {
		return (ATE::CharFeaturesRef) getAIObjectHandle(env, obj, "character style");
	}
	
	inline ATE::ParaFeaturesRef getParaFeaturesHandle(JNIEnv *env, jobject obj) {
		return (ATE::ParaFeaturesRef) getAIObjectHandle(env, obj, "paragraph style");
	}
	
	jobject wrapTextRangeRef(JNIEnv *env, ATE::TextRangeRef range);
	
	// AI Wrap Handles
	jobject wrapArtHandle(JNIEnv *env, AIArtHandle art, AIDocumentHandle doc = NULL, AIDictionaryRef dictionary = NULL, short type = -1);
	bool updateArtIfWrapped(JNIEnv *env, AIArtHandle art);
	void changeArtHandle(JNIEnv *env, jobject itemObject, AIArtHandle art, AIDocumentHandle doc = NULL, AIDictionaryRef dictionary = NULL);
	jobject getIfWrapped(JNIEnv *env, AIArtHandle handle);

	jobject wrapLayerHandle(JNIEnv *env, AILayerHandle layer, AIDocumentHandle doc = NULL);
	jobject wrapMenuItemHandle(JNIEnv *env, AIMenuItemHandle item);
	
	jobject wrapDictionaryHandle(JNIEnv *env, AIDictionaryRef dictionary, AIDocumentHandle doc = NULL);

	void commit(JNIEnv *env);
	void resumeSuspendedDocuments();
	
	ASErr selectionChanged();
	
	// AI Tool
	ASErr toolHandleEvent(const char * selector, AIToolMessage *message);

	// AI LiveEffect
	AILiveEffectParamContext getLiveEffectContext(JNIEnv *env, jobject parameters);
	ASErr liveEffectEditParameters(AILiveEffectEditParamMessage *message);
	ASErr liveEffectCalculate(AILiveEffectGoMessage *message);
	ASErr liveEffectInterpolate(AILiveEffectInterpParamMessage *message);
	ASErr liveEffectGetInputType(AILiveEffectInputTypeMessage *message);
	
	// AI MenuItem
	ASErr menuItemExecute(AIMenuMessage *message);
	ASErr menuItemUpdate(AIMenuMessage *message, long inArtwork, long isSelected, long isTrue);

	// AI Timer
	ASErr timerExecute(AITimerMessage *message);

	// AI Annotator
	ASErr annotatorDraw(AIAnnotatorMessage *message);
	ASErr annotatorInvalidate(AIAnnotatorMessage *message);
	
	// ADM CallbackListener
	void callOnNotify(jobject handler, ADMNotifierRef notifier); 
	void callOnNotify(jobject handler, char *notifier); 
	void callOnDestroy(jobject handler); 
	bool callOnTrack(jobject handler, ADMTrackerRef tracker);
	void callOnDraw(jobject handler, ADMDrawerRef drawer);

	ASErr onHandleEvent(int type);

	// ADM Handles
	int getADMObjectHandle(JNIEnv *env, jobject obj, const char *name);
	int getADMListHandle(JNIEnv *env, jobject obj, const char *name);

	// Menu items are in the ADM package in Scriptographer, although natively they belong to AI
	inline AIMenuItemHandle getMenuItemHandle(JNIEnv *env, jobject obj) {
		return (AIMenuItemHandle) getADMObjectHandle(env, obj, "menu item");
	}
	
	inline AIMenuGroup getMenuGroupHandle(JNIEnv *env, jobject obj) {
		return (AIMenuGroup) getADMObjectHandle(env, obj, "menu group");
	}

	inline ADMDialogRef getDialogHandle(JNIEnv *env, jobject obj) {
		return (ADMDialogRef) getADMObjectHandle(env, obj, "dialog");
	}

	inline ADMDrawerRef getDrawerHandle(JNIEnv *env, jobject obj) {
		return (ADMDrawerRef) getADMObjectHandle(env, obj, "drawer");
	}

	inline ADMTrackerRef getTrackerHandle(JNIEnv *env, jobject obj) {
		return (ADMTrackerRef) getADMObjectHandle(env, obj, "tracker");
	}

	inline ADMIconRef getIconHandle(JNIEnv *env, jobject obj) {
		return (ADMIconRef) getADMObjectHandle(env, obj, "icon");
	}

	inline ADMImageRef getImageHandle(JNIEnv *env, jobject obj) {
		return (ADMImageRef) getADMObjectHandle(env, obj, "image");
	}

	inline ADMItemRef getItemHandle(JNIEnv *env, jobject obj) {
		return (ADMItemRef) getADMObjectHandle(env, obj, "item");
	}

	inline ADMListRef getListHandle(JNIEnv *env, jobject obj) {
		return (ADMListRef) getADMListHandle(env, obj, "list");
	}

	inline ADMHierarchyListRef getHierarchyListHandle(JNIEnv *env, jobject obj) {
		return (ADMHierarchyListRef) getADMListHandle(env, obj, "hierarchy list");
	}

	inline ADMEntryRef getListEntryHandle(JNIEnv *env, jobject obj) {
		return (ADMEntryRef) getADMObjectHandle(env, obj, "list entry");
	}

	inline ADMListEntryRef getHierarchyListEntryHandle(JNIEnv *env, jobject obj) {
		return (ADMListEntryRef) getADMObjectHandle(env, obj, "hierarchy list entry");
	}
	
	// ADM Objects
	jobject getDialogObject(ADMDialogRef dlg);
	jobject getItemObject(ADMItemRef item);
	jobject getListObject(ADMListRef list);
	jobject getListObject(ADMHierarchyListRef list);
	jobject getListEntryObject(ADMEntryRef list);
	jobject getListEntryObject(ADMListEntryRef list);
		
	// JNI stuff:
	JNIEnv *getEnv();
	
	jstring convertString(JNIEnv *env, const char *str);
	jstring convertString(JNIEnv *env, unsigned char *str);
	char *convertString(JNIEnv *env, jstring jstr, int minLength = 0);
	jstring convertString(JNIEnv *env, const ASUnicode *str, int length = -1);
	ASUnicode *convertString_ASUnicode(JNIEnv *env, jstring jstr);
#if kPluginInterfaceVersion < kAI12
	unsigned char *convertString_Pascal(JNIEnv *env, jstring jstr, int minLength = 0);
#else
	jstring convertString(JNIEnv *env, ai::UnicodeString &str);
	ai::UnicodeString convertString_UnicodeString(JNIEnv *env, jstring jstr);
#endif

	void throwException(JNIEnv *env, const char* name, const char* msg);
	void throwException(JNIEnv *env, const char* msg);

	// for reflection:
	jclass findClass(JNIEnv *env, const char *name);
	jclass loadClass(JNIEnv *env, const char *name);
	
	jmethodID getMethodID(JNIEnv *env, jclass cls, const char *name, const char *signature);
	jmethodID getStaticMethodID(JNIEnv *env, jclass cls, const char *name, const char *signature);
	jmethodID getConstructorID(JNIEnv *env, jclass cls, const char *signature);
	
	jfieldID getFieldID(JNIEnv *env, jclass cls, const char *name, const char *signature);
	jfieldID getStaticFieldID(JNIEnv *env, jclass cls, const char *name, const char *signature);
	
	// wrappers for JNI function with added exception handling
	jobject newObject(JNIEnv *env, jclass cls, jmethodID ctr, ...);

	// get<type>Field(JNIEnv * env, jobject obj, jfieldID fid);
	JNI_DECLARE_GETFIELD_FUNCTIONS
	// set<type>Field(JNIEnv * env, jobject obj, jfieldID fid, <type> val);
	JNI_DECLARE_SETFIELD_FUNCTIONS
	// getStatic<type>Field(JNIEnv * env, jclass cls, const char *name, const char *signature);
	JNI_DECLARE_GETSTATICFIELD_FUNCTIONS
	// call<type>Method(JNIEnv * env, jobject obj, jmethodID mid, ...);
	// callStatic<type>Method(JNIEnv * env, jclass cls, jmethodID mid, ...);
	// call<type>MethodReport(JNIEnv * env, jobject obj, jmethodID mid, ...);
	// callStatic<type>MethodReport(JNIEnv * env, jclass cls, jmethodID mid, ...);
	JNI_DECLARE_CALLMETHOD_FUNCTIONS
};

extern ScriptographerEngine *gEngine;

// Callback function pointers for dynamically loading JNI invocation functions on Windows
typedef jint (JNICALL *CreateJavaVMProc)(JavaVM **jvm, void **env, void *args);
typedef jint (JNICALL *GetDefaultJavaVMInitArgsProc)(void *args);

#ifdef WIN_ENV
#define PATH_SEP_CHR '\\'
#define PATH_SEP_STR "\\"
#define NATIVE_NEWLINE "\r\n"
#else
#define PATH_SEP_CHR '/'
#define PATH_SEP_STR "/"
#define NATIVE_NEWLINE "\r"
#endif

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define ABS(a) ((a) >= 0 ? (a) : -(a))
