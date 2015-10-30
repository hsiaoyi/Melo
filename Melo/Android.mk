LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../cocos2d/cocos)


LOCAL_MODULE 	:= melo_static
LOCAL_MODULE_FILENAME := libmelostatic

LOCAL_SRC_FILES :=  MLMath.cpp \
					MLInputMgr.cpp \
					MLApp.cpp \
					MLSprite.cpp \
					MLScriptMgr.cpp \
					MLLayer.cpp \
					MLSceneMgr.cpp \
					MLLabel.cpp \
					MLBaseLayer.cpp \
					MLTTFFont.cpp \
					MLFontMgr.cpp \
					MLAppDelegate.cpp \
					MLCCScene.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/. \
					$(LOCAL_PATH)/../cocos2d \
					$(LOCAL_PATH)/../cocos2d/cocos \
					$(LOCAL_PATH)/../cocos2d/external \
					$(LOCAL_PATH)/../cocos2d/external/lua/luajit/include \
					$(LOCAL_PATH)/../cocos2d/external/freetype2/include/android/freetype2 \
					

LOCAL_STATIC_LIBRARIES := cocos2dx_static

LOCAL_EXPORT_C_INCLUDES :=  $(LOCAL_PATH)/. \
							$(LOCAL_PATH)/../cocos2d \
							$(LOCAL_PATH)/../cocos2d/cocos \
							$(LOCAL_PATH)/../cocos2d/external \
							$(LOCAL_PATH)/../cocos2d/external/lua/luajit/include \
							$(LOCAL_PATH)/../cocos2d/external/freetype2/include/android/freetype2 \

							
LOCAL_STATIC_LIBRARIES := cocos2dx_static
LOCAL_STATIC_LIBRARIES += cocos_freetype2_static
LOCAL_STATIC_LIBRARIES += luajit_static

LOCAL_CFLAGS   :=  -DUSE_FILE32API
LOCAL_CFLAGS   +=  -fexceptions
LOCAL_CFLAGS   +=  -DMELO_SUPPORT
LOCAL_CFLAGS   +=  -DUSE_COCOS2DX

#LOCAL_CPPFLAGS := -Wno-deprecated-declarations -Wno-extern-c-compat
LOCAL_EXPORT_CFLAGS   := -DUSE_FILE32API
LOCAL_EXPORT_CFLAGS   += -DMELO_SUPPORT
#LOCAL_EXPORT_CPPFLAGS := -Wno-deprecated-declarations -Wno-extern-c-compat

include $(BUILD_STATIC_LIBRARY)

$(call import-module,cocos)
$(call import-module,freetype2/prebuilt/android)
$(call import-module,lua/luajit/prebuilt/android)