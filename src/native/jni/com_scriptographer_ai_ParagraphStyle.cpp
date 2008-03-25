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

#include "StdHeaders.h"
#include "ScriptographerEngine.h"
#include "aiGlobals.h"
#include "com_scriptographer_ai_ParagraphStyle.h"

/*
 * com.scriptographer.ai.ParagraphStyle
 */

using namespace ATE;

/*
 * int nativeCreate()
 */
JNIEXPORT jint JNICALL Java_com_scriptographer_ai_ParagraphStyle_nativeCreate(JNIEnv *env, jclass cls) {
	try {
		ParaFeaturesRef features;
		if (!sParaFeatures->Initialize(&features)) {
			// add reference to the handle, which will be released in ParagraphStyle.finalize
			sParaFeatures->AddRef(features);
			return (jint) features;
		}
	} EXCEPTION_CONVERT(env);
	return 0;
}

/*
 * int nativeClone()
 */
JNIEXPORT jint JNICALL Java_com_scriptographer_ai_ParagraphStyle_nativeClone(JNIEnv *env, jobject obj) {
	try {
		ParaFeaturesRef features = gEngine->getParaFeaturesRef(env, obj);
		ParaFeaturesRef clone;
		if (!sParaFeatures->Clone(features, &clone)) {
			// add reference to the handle, which will be released in ParagraphStyle.finalize
			sParaFeatures->AddRef(clone);
			return (jint) clone;
		}
	} EXCEPTION_CONVERT(env);
	return 0;
}

/*
 * void nativeSetStyle(int handle, int rangeHandle)
 */
JNIEXPORT void JNICALL Java_com_scriptographer_ai_ParagraphStyle_nativeSetStyle(JNIEnv *env, jobject obj, jint handle, jint rangeHandle) {
	try {
		sTextRange->SetLocalParaFeatures((TextRangeRef) rangeHandle, (ParaFeaturesRef) handle);
	} EXCEPTION_CONVERT(env);
}

/*
 * void release()
 */
JNIEXPORT void JNICALL Java_com_scriptographer_ai_ParagraphStyle_release(JNIEnv *env, jobject obj) {
	try {
		ParaFeaturesRef features = (ParaFeaturesRef) gEngine->getIntField(env, obj, gEngine->fid_ai_NativeObject_handle);
		if (features != NULL) {
			sParaFeatures->Release(features);
			gEngine->setIntField(env, obj, gEngine->fid_ai_NativeObject_handle, 0);
		}
	} EXCEPTION_CONVERT(env);
}

/*
 * java.lang.Integer getJustification()
 */
JNIEXPORT jobject JNICALL Java_com_scriptographer_ai_ParagraphStyle_getJustification(JNIEnv *env, jobject obj) {
	PARAGRAPHSTYLE_GET_ENUM(Justification, ParagraphJustification)
}

/*
 * void setJustification(java.lang.Integer value)
 */
JNIEXPORT void JNICALL Java_com_scriptographer_ai_ParagraphStyle_setJustification(JNIEnv *env, jobject obj, jobject value) {
	PARAGRAPHSTYLE_SET_ENUM(Justification, ParagraphJustification)
}

/*
 * java.lang.Float getFirstLineIndent()
 */
JNIEXPORT jobject JNICALL Java_com_scriptographer_ai_ParagraphStyle_getFirstLineIndent(JNIEnv *env, jobject obj) {
	PARAGRAPHSTYLE_GET_FLOAT(FirstLineIndent)
}

/*
 * void setFirstLineIndent(java.lang.Float value)
 */
JNIEXPORT void JNICALL Java_com_scriptographer_ai_ParagraphStyle_setFirstLineIndent(JNIEnv *env, jobject obj, jobject value) {
	PARAGRAPHSTYLE_SET_FLOAT(FirstLineIndent)
}

/*
 * java.lang.Float getStartIndent()
 */
JNIEXPORT jobject JNICALL Java_com_scriptographer_ai_ParagraphStyle_getStartIndent(JNIEnv *env, jobject obj) {
	PARAGRAPHSTYLE_GET_FLOAT(StartIndent)
}

/*
 * void setStartIndent(java.lang.Float value)
 */
JNIEXPORT void JNICALL Java_com_scriptographer_ai_ParagraphStyle_setStartIndent(JNIEnv *env, jobject obj, jobject value) {
	PARAGRAPHSTYLE_SET_FLOAT(StartIndent)
}

/*
 * java.lang.Float getEndIndent()
 */
JNIEXPORT jobject JNICALL Java_com_scriptographer_ai_ParagraphStyle_getEndIndent(JNIEnv *env, jobject obj) {
	PARAGRAPHSTYLE_GET_FLOAT(EndIndent)
}

/*
 * void setEndIndent(java.lang.Float value)
 */
JNIEXPORT void JNICALL Java_com_scriptographer_ai_ParagraphStyle_setEndIndent(JNIEnv *env, jobject obj, jobject value) {
	PARAGRAPHSTYLE_SET_FLOAT(EndIndent)
}

/*
 * java.lang.Float getSpaceBefore()
 */
JNIEXPORT jobject JNICALL Java_com_scriptographer_ai_ParagraphStyle_getSpaceBefore(JNIEnv *env, jobject obj) {
	PARAGRAPHSTYLE_GET_FLOAT(SpaceBefore)
}

/*
 * void setSpaceBefore(java.lang.Float value)
 */
JNIEXPORT void JNICALL Java_com_scriptographer_ai_ParagraphStyle_setSpaceBefore(JNIEnv *env, jobject obj, jobject value) {
	PARAGRAPHSTYLE_SET_FLOAT(SpaceBefore)
}

/*
 * java.lang.Float getSpaceAfter()
 */
JNIEXPORT jobject JNICALL Java_com_scriptographer_ai_ParagraphStyle_getSpaceAfter(JNIEnv *env, jobject obj) {
	PARAGRAPHSTYLE_GET_FLOAT(SpaceAfter)
}

/*
 * void setSpaceAfter(java.lang.Float value)
 */
JNIEXPORT void JNICALL Java_com_scriptographer_ai_ParagraphStyle_setSpaceAfter(JNIEnv *env, jobject obj, jobject value) {
	PARAGRAPHSTYLE_SET_FLOAT(SpaceAfter)
}

/*
 * java.lang.Boolean getHyphenation()
 */
JNIEXPORT jobject JNICALL Java_com_scriptographer_ai_ParagraphStyle_getHyphenation(JNIEnv *env, jobject obj) {
	PARAGRAPHSTYLE_GET_BOOLEAN(AutoHyphenate)
}

/*
 * void setHyphenation(java.lang.Boolean value)
 */
JNIEXPORT void JNICALL Java_com_scriptographer_ai_ParagraphStyle_setHyphenation(JNIEnv *env, jobject obj, jobject value) {
	PARAGRAPHSTYLE_SET_BOOLEAN(AutoHyphenate)
}

/*
 * java.lang.Integer getHyphenatedWordSize()
 */
JNIEXPORT jobject JNICALL Java_com_scriptographer_ai_ParagraphStyle_getHyphenatedWordSize(JNIEnv *env, jobject obj) {
	PARAGRAPHSTYLE_GET_INTEGER(HyphenatedWordSize)
}

/*
 * void setHyphenatedWordSize(java.lang.Integer value)
 */
JNIEXPORT void JNICALL Java_com_scriptographer_ai_ParagraphStyle_setHyphenatedWordSize(JNIEnv *env, jobject obj, jobject value) {
	PARAGRAPHSTYLE_SET_INTEGER(HyphenatedWordSize)
}

/*
 * java.lang.Integer getPreHyphenSize()
 */
JNIEXPORT jobject JNICALL Java_com_scriptographer_ai_ParagraphStyle_getPreHyphenSize(JNIEnv *env, jobject obj) {
	PARAGRAPHSTYLE_GET_INTEGER(PreHyphenSize)
}

/*
 * void setPreHyphenSize(java.lang.Integer value)
 */
JNIEXPORT void JNICALL Java_com_scriptographer_ai_ParagraphStyle_setPreHyphenSize(JNIEnv *env, jobject obj, jobject value) {
	PARAGRAPHSTYLE_SET_INTEGER(PreHyphenSize)
}

/*
 * java.lang.Integer getPostHyphenSize()
 */
JNIEXPORT jobject JNICALL Java_com_scriptographer_ai_ParagraphStyle_getPostHyphenSize(JNIEnv *env, jobject obj) {
	PARAGRAPHSTYLE_GET_INTEGER(PostHyphenSize)
}

/*
 * void setPostHyphenSize(java.lang.Integer value)
 */
JNIEXPORT void JNICALL Java_com_scriptographer_ai_ParagraphStyle_setPostHyphenSize(JNIEnv *env, jobject obj, jobject value) {
	PARAGRAPHSTYLE_SET_INTEGER(PostHyphenSize)
}

/*
 * java.lang.Integer getConsecutiveHyphenLimit()
 */
JNIEXPORT jobject JNICALL Java_com_scriptographer_ai_ParagraphStyle_getConsecutiveHyphenLimit(JNIEnv *env, jobject obj) {
	PARAGRAPHSTYLE_GET_INTEGER(ConsecutiveHyphenLimit)
}

/*
 * void setConsecutiveHyphenLimit(java.lang.Integer value)
 */
JNIEXPORT void JNICALL Java_com_scriptographer_ai_ParagraphStyle_setConsecutiveHyphenLimit(JNIEnv *env, jobject obj, jobject value) {
	PARAGRAPHSTYLE_SET_INTEGER(ConsecutiveHyphenLimit)
}

/*
 * java.lang.Float getHyphenationZone()
 */
JNIEXPORT jobject JNICALL Java_com_scriptographer_ai_ParagraphStyle_getHyphenationZone(JNIEnv *env, jobject obj) {
	PARAGRAPHSTYLE_GET_FLOAT(HyphenationZone)
}

/*
 * void setHyphenationZone(java.lang.Float value)
 */
JNIEXPORT void JNICALL Java_com_scriptographer_ai_ParagraphStyle_setHyphenationZone(JNIEnv *env, jobject obj, jobject value) {
	PARAGRAPHSTYLE_SET_FLOAT(HyphenationZone)
}

/*
 * java.lang.Boolean getHyphenateCapitalized()
 */
JNIEXPORT jobject JNICALL Java_com_scriptographer_ai_ParagraphStyle_getHyphenateCapitalized(JNIEnv *env, jobject obj) {
	PARAGRAPHSTYLE_GET_BOOLEAN(HyphenateCapitalized)
}

/*
 * void setHyphenateCapitalized(java.lang.Boolean value)
 */
JNIEXPORT void JNICALL Java_com_scriptographer_ai_ParagraphStyle_setHyphenateCapitalized(JNIEnv *env, jobject obj, jobject value) {
	PARAGRAPHSTYLE_SET_BOOLEAN(HyphenateCapitalized)
}

/*
 * java.lang.Float getHyphenationPreference()
 */
JNIEXPORT jobject JNICALL Java_com_scriptographer_ai_ParagraphStyle_getHyphenationPreference(JNIEnv *env, jobject obj) {
	PARAGRAPHSTYLE_GET_FLOAT(HyphenationPreference)
}

/*
 * void setHyphenationPreference(java.lang.Float value)
 */
JNIEXPORT void JNICALL Java_com_scriptographer_ai_ParagraphStyle_setHyphenationPreference(JNIEnv *env, jobject obj, jobject value) {
	PARAGRAPHSTYLE_SET_FLOAT(HyphenationPreference)
}

/*
 * java.lang.Float getDesiredWordSpacing()
 */
JNIEXPORT jobject JNICALL Java_com_scriptographer_ai_ParagraphStyle_getDesiredWordSpacing(JNIEnv *env, jobject obj) {
	PARAGRAPHSTYLE_GET_FLOAT(DesiredWordSpacing)
}

/*
 * void setDesiredWordSpacing(java.lang.Float value)
 */
JNIEXPORT void JNICALL Java_com_scriptographer_ai_ParagraphStyle_setDesiredWordSpacing(JNIEnv *env, jobject obj, jobject value) {
	PARAGRAPHSTYLE_SET_FLOAT_CLEAR(DesiredWordSpacing, WordSpacing)
}

/*
 * java.lang.Float getMaximumWordSpacing()
 */
JNIEXPORT jobject JNICALL Java_com_scriptographer_ai_ParagraphStyle_getMaximumWordSpacing(JNIEnv *env, jobject obj) {
	PARAGRAPHSTYLE_GET_FLOAT(MaxWordSpacing)
}

/*
 * void setMaximumWordSpacing(java.lang.Float value)
 */
JNIEXPORT void JNICALL Java_com_scriptographer_ai_ParagraphStyle_setMaximumWordSpacing(JNIEnv *env, jobject obj, jobject value) {
	PARAGRAPHSTYLE_SET_FLOAT_CLEAR(MaxWordSpacing, WordSpacing)
}

/*
 * java.lang.Float getMinimumWordSpacing()
 */
JNIEXPORT jobject JNICALL Java_com_scriptographer_ai_ParagraphStyle_getMinimumWordSpacing(JNIEnv *env, jobject obj) {
	PARAGRAPHSTYLE_GET_FLOAT(MinWordSpacing)
}

/*
 * void setMinimumWordSpacing(java.lang.Float value)
 */
JNIEXPORT void JNICALL Java_com_scriptographer_ai_ParagraphStyle_setMinimumWordSpacing(JNIEnv *env, jobject obj, jobject value) {
	PARAGRAPHSTYLE_SET_FLOAT_CLEAR(MinWordSpacing, WordSpacing)
}

/*
 * java.lang.Float getDesiredLetterSpacing()
 */
JNIEXPORT jobject JNICALL Java_com_scriptographer_ai_ParagraphStyle_getDesiredLetterSpacing(JNIEnv *env, jobject obj) {
	PARAGRAPHSTYLE_GET_FLOAT(DesiredLetterSpacing)
}

/*
 * void setDesiredLetterSpacing(java.lang.Float value)
 */
JNIEXPORT void JNICALL Java_com_scriptographer_ai_ParagraphStyle_setDesiredLetterSpacing(JNIEnv *env, jobject obj, jobject value) {
	PARAGRAPHSTYLE_SET_FLOAT_CLEAR(DesiredLetterSpacing, LetterSpacing)
}

/*
 * java.lang.Float getMaximumLetterSpacing()
 */
JNIEXPORT jobject JNICALL Java_com_scriptographer_ai_ParagraphStyle_getMaximumLetterSpacing(JNIEnv *env, jobject obj) {
	PARAGRAPHSTYLE_GET_FLOAT(MaxLetterSpacing)
}

/*
 * void setMaximumLetterSpacing(java.lang.Float value)
 */
JNIEXPORT void JNICALL Java_com_scriptographer_ai_ParagraphStyle_setMaximumLetterSpacing(JNIEnv *env, jobject obj, jobject value) {
	PARAGRAPHSTYLE_SET_FLOAT_CLEAR(MaxLetterSpacing, LetterSpacing)
}

/*
 * java.lang.Float getMinimumLetterSpacing()
 */
JNIEXPORT jobject JNICALL Java_com_scriptographer_ai_ParagraphStyle_getMinimumLetterSpacing(JNIEnv *env, jobject obj) {
	PARAGRAPHSTYLE_GET_FLOAT(MinLetterSpacing)
}

/*
 * void setMinimumLetterSpacing(java.lang.Float value)
 */
JNIEXPORT void JNICALL Java_com_scriptographer_ai_ParagraphStyle_setMinimumLetterSpacing(JNIEnv *env, jobject obj, jobject value) {
	PARAGRAPHSTYLE_SET_FLOAT_CLEAR(MinLetterSpacing, LetterSpacing)
}

/*
 * java.lang.Float getDesiredGlyphScaling()
 */
JNIEXPORT jobject JNICALL Java_com_scriptographer_ai_ParagraphStyle_getDesiredGlyphScaling(JNIEnv *env, jobject obj) {
	PARAGRAPHSTYLE_GET_FLOAT(DesiredGlyphScaling)
}

/*
 * void setDesiredGlyphScaling(java.lang.Float value)
 */
JNIEXPORT void JNICALL Java_com_scriptographer_ai_ParagraphStyle_setDesiredGlyphScaling(JNIEnv *env, jobject obj, jobject value) {
	PARAGRAPHSTYLE_SET_FLOAT_CLEAR(DesiredGlyphScaling, GlyphScaling)
}

/*
 * java.lang.Float getMaximumGlyphScaling()
 */
JNIEXPORT jobject JNICALL Java_com_scriptographer_ai_ParagraphStyle_getMaximumGlyphScaling(JNIEnv *env, jobject obj) {
	PARAGRAPHSTYLE_GET_FLOAT(MaxGlyphScaling)
}

/*
 * void setMaximumGlyphScaling(java.lang.Float value)
 */
JNIEXPORT void JNICALL Java_com_scriptographer_ai_ParagraphStyle_setMaximumGlyphScaling(JNIEnv *env, jobject obj, jobject value) {
	PARAGRAPHSTYLE_SET_FLOAT_CLEAR(MaxGlyphScaling, GlyphScaling)
}

/*
 * java.lang.Float getMinimumGlyphScaling()
 */
JNIEXPORT jobject JNICALL Java_com_scriptographer_ai_ParagraphStyle_getMinimumGlyphScaling(JNIEnv *env, jobject obj) {
	PARAGRAPHSTYLE_GET_FLOAT(MinGlyphScaling)
}

/*
 * void setMinimumGlyphScaling(java.lang.Float value)
 */
JNIEXPORT void JNICALL Java_com_scriptographer_ai_ParagraphStyle_setMinimumGlyphScaling(JNIEnv *env, jobject obj, jobject value) {
	PARAGRAPHSTYLE_SET_FLOAT_CLEAR(MinGlyphScaling, GlyphScaling)
}

/*
 * java.lang.Integer getSingleWordJustification()
 */
JNIEXPORT jobject JNICALL Java_com_scriptographer_ai_ParagraphStyle_getSingleWordJustification(JNIEnv *env, jobject obj) {
	PARAGRAPHSTYLE_GET_ENUM(SingleWordJustification, ParagraphJustification)
}

/*
 * void setSingleWordJustification(java.lang.Integer value)
 */
JNIEXPORT void JNICALL Java_com_scriptographer_ai_ParagraphStyle_setSingleWordJustification(JNIEnv *env, jobject obj, jobject value) {
	PARAGRAPHSTYLE_SET_ENUM(SingleWordJustification, ParagraphJustification)
}

/*
 * java.lang.Float getAutoLeadingPercentage()
 */
JNIEXPORT jobject JNICALL Java_com_scriptographer_ai_ParagraphStyle_getAutoLeadingPercentage(JNIEnv *env, jobject obj) {
	PARAGRAPHSTYLE_GET_FLOAT(AutoLeadingPercentage)
}

/*
 * void setAutoLeadingPercentage(java.lang.Float value)
 */
JNIEXPORT void JNICALL Java_com_scriptographer_ai_ParagraphStyle_setAutoLeadingPercentage(JNIEnv *env, jobject obj, jobject value) {
	PARAGRAPHSTYLE_SET_FLOAT(AutoLeadingPercentage)
}

/*
 * java.lang.Integer getLeadingType()
 */
JNIEXPORT jobject JNICALL Java_com_scriptographer_ai_ParagraphStyle_getLeadingType(JNIEnv *env, jobject obj) {
	PARAGRAPHSTYLE_GET_ENUM(LeadingType, LeadingType)
}

/*
 * void setLeadingType(java.lang.Integer value)
 */
JNIEXPORT void JNICALL Java_com_scriptographer_ai_ParagraphStyle_setLeadingType(JNIEnv *env, jobject obj, jobject value) {
	PARAGRAPHSTYLE_SET_ENUM(LeadingType, LeadingType)
}

/*
 * java.lang.Float getDefaultTabWidth()
 */
JNIEXPORT jobject JNICALL Java_com_scriptographer_ai_ParagraphStyle_getDefaultTabWidth(JNIEnv *env, jobject obj) {
	PARAGRAPHSTYLE_GET_FLOAT(DefaultTabWidth)
}

/*
 * void setDefaultTabWidth(java.lang.Float value)
 */
JNIEXPORT void JNICALL Java_com_scriptographer_ai_ParagraphStyle_setDefaultTabWidth(JNIEnv *env, jobject obj, jobject value) {
	try {
		// no macro here as clearing is not possible for this value
		ParaFeaturesRef features = gEngine->getParaFeaturesRef(env, obj);
		if (value != NULL && !sParaFeatures->SetDefaultTabWidth(features, (ASReal) gEngine->callFloatMethod(env, value, gEngine->mid_Number_floatValue)))
			gEngine->callVoidMethod(env, obj, gEngine->mid_ai_ParagraphStyle_markSetStyle);
	} EXCEPTION_CONVERT(env);
}
