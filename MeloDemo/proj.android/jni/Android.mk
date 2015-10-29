LOCAL_PATH := $(call my-dir)

#==============================================================

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../)

LOCAL_MODULE := melodemo_shared

LOCAL_MODULE_FILENAME := libmelodemo

LOCAL_SRC_FILES := MeloDemo/melomain.cpp \
                   ../../MeloDemo/MDAppDelegate.cpp \
                   ../../MeloDemo/MDGameScene.cpp \
                   ../../MeloDemo/MDLuaWrapper.cpp \
                   #../../MeloDemo/HelloWorldScene.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../MeloDemo \
					$(LOCAL_PATH)/../../../Melo \
					$(LOCAL_PATH)/../../../.. \
					$(LOCAL_PATH)/../../../cocos2d/external/lua/luajit/include \
					$(LOCAL_PATH)/../../../cocos2d/external/freetype2/include/android/freetype2 \

#LOCAL_STATIC_LIBRARIES := cocos2dx_static
LOCAL_STATIC_LIBRARIES := melo_static

LOCAL_CFLAGS   :=  -DMELO_SUPPORT
LOCAL_CFLAGS   +=  -DUSE_COCOS2DX

include $(BUILD_SHARED_LIBRARY)
#==============================================================
#$(call import-module,.)
#$(call import-module,cocos)
$(call import-module,Melo)