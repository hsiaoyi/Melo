LOCAL_PATH := $(call my-dir)

#==============================================================

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)
#$(call import-add-path,$(LOCAL_PATH)/../../../)

LOCAL_MODULE := melodemo_shared

LOCAL_MODULE_FILENAME := libmelodemo

LOCAL_SRC_FILES :=  ../../../Melo/MLMath.cpp \
					../../../Melo/MLInputMgr.cpp \
					../../../Melo/MLApp.cpp \
					../../../Melo/MLSprite.cpp \
					../../../Melo/MLScriptMgr.cpp \
					../../../Melo/MLLayer.cpp \
					../../../Melo/MLSceneMgr.cpp \
					../../../Melo/MLLabel.cpp \
					../../../Melo/MLBaseLayer.cpp \
					../../../Melo/MLTTFFont.cpp \
					../../../Melo/MLFontMgr.cpp \
					../../../Melo/MLAppDelegate.cpp \
					../../../Melo/MLCCScene.cpp \
					MeloDemo/melomain.cpp \
                   ../../MeloDemo/MDAppDelegate.cpp \
                   ../../MeloDemo/MDGameScene.cpp \
                   ../../MeloDemo/MDLuaWrapper.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../MeloDemo \
					$(LOCAL_PATH)/../../../Melo \
					$(LOCAL_PATH)/../../../.. \
					$(LOCAL_PATH)/../../../cocos2d/external/lua/luajit/include \
					$(LOCAL_PATH)/../../../cocos2d/external/freetype2/include/android/freetype2 \
					$(LOCAL_PATH)/../../../cocos2d \
					$(LOCAL_PATH)/../../../cocos2d/cocos \
					$(LOCAL_PATH)/../../../cocos2d/external \


LOCAL_STATIC_LIBRARIES := cocos2dx_static
LOCAL_STATIC_LIBRARIES += cocos_freetype2_static
LOCAL_STATIC_LIBRARIES += luajit_static
#LOCAL_STATIC_LIBRARIES += melo_static

LOCAL_CFLAGS   :=  -DMELO_SUPPORT
LOCAL_CFLAGS   +=  -DUSE_COCOS2DX

include $(BUILD_SHARED_LIBRARY)
#==============================================================
#$(call import-module,.)
$(call import-module,cocos)
#$(call import-module,Melo)
$(call import-module,freetype2/prebuilt/android)
$(call import-module,lua/luajit/prebuilt/android)