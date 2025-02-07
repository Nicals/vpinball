# Defines adaptee VPinball library.
# This is a copy-paste from CMakeLists_gl-linux-x64.txt adapted to generate
# a library from VPinball standalone.

set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH "$ORIGIN")

# XXX: Hopefully temporary..
set(VPINBALL_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../..)

add_library(glad SHARED
  ${VPINBALL_SOURCE_DIR}/third-party/include/glad/src/gl.c
)

target_include_directories(glad PUBLIC
  ${VPINBALL_SOURCE_DIR}/third-party/include/glad/include
)

find_package(BISON 3.7.5 REQUIRED)
bison_target(vbsparser
  ${VPINBALL_SOURCE_DIR}/standalone/inc/wine/dlls/vbscript/parser.y
  ${VPINBALL_SOURCE_DIR}/standalone/inc/wine/dlls/vbscript/parser.tab.c 
	DEFINES_FILE
    ${VPINBALL_SOURCE_DIR}/standalone/inc/wine/dlls/vbscript/parser.tab.h
)

add_library(wine STATIC
  ${VPINBALL_SOURCE_DIR}/standalone/inc/wine/dlls/atl/atl.c

  ${VPINBALL_SOURCE_DIR}/standalone/inc/wine/dlls/oleaut32/oleaut.c
  ${VPINBALL_SOURCE_DIR}/standalone/inc/wine/dlls/oleaut32/variant.c
  ${VPINBALL_SOURCE_DIR}/standalone/inc/wine/dlls/oleaut32/varformat.c
  ${VPINBALL_SOURCE_DIR}/standalone/inc/wine/dlls/oleaut32/vartype.c
  ${VPINBALL_SOURCE_DIR}/standalone/inc/wine/dlls/oleaut32/safearray.c

  ${VPINBALL_SOURCE_DIR}/standalone/inc/wine/dlls/vbscript/compile.c
  ${VPINBALL_SOURCE_DIR}/standalone/inc/wine/dlls/vbscript/global.c
  ${VPINBALL_SOURCE_DIR}/standalone/inc/wine/dlls/vbscript/interp.c
  ${VPINBALL_SOURCE_DIR}/standalone/inc/wine/dlls/vbscript/lex.c
  ${VPINBALL_SOURCE_DIR}/standalone/inc/wine/dlls/vbscript/regexp.c
  ${VPINBALL_SOURCE_DIR}/standalone/inc/wine/dlls/vbscript/utils.c
  ${VPINBALL_SOURCE_DIR}/standalone/inc/wine/dlls/vbscript/vbdisp.c
  ${VPINBALL_SOURCE_DIR}/standalone/inc/wine/dlls/vbscript/vbregexp.c
  ${VPINBALL_SOURCE_DIR}/standalone/inc/wine/dlls/vbscript/vbscript.c
  ${VPINBALL_SOURCE_DIR}/standalone/inc/wine/dlls/vbscript/vbscript_main.c
  ${VPINBALL_SOURCE_DIR}/standalone/inc/wine/dlls/vbscript/parser.tab.c

  ${VPINBALL_SOURCE_DIR}/standalone/inc/wine/dlls/scrrun/dictionary.c
  ${VPINBALL_SOURCE_DIR}/standalone/inc/wine/dlls/scrrun/filesystem.c
  ${VPINBALL_SOURCE_DIR}/standalone/inc/wine/dlls/scrrun/scrrun.c

  ${VPINBALL_SOURCE_DIR}/standalone/inc/wine/dlls/kernelbase/locale.c

  ${VPINBALL_SOURCE_DIR}/standalone/inc/wine/wine.c
)

target_include_directories(wine PUBLIC
  ${VPINBALL_SOURCE_DIR}
  ${VPINBALL_SOURCE_DIR}/standalone/inc/wine/include
  $VPINBALL_SOURCE_DIR}/standalone/inc/wine/dlls/atl
  ${VPINBALL_SOURCE_DIR}/standalone/inc/wine/dlls/vbscript
  ${VPINBALL_SOURCE_DIR}/standalone/inc/wine/dlls/oleaut32
  ${VPINBALL_SOURCE_DIR}/standalone/inc/wine/dlls/kernelbase
)
set_property(TARGET wine PROPERTY POSITION_INDEPENDENT_CODE ON)

target_compile_definitions(wine PUBLIC
  "__forceinline=__attribute__((always_inline)) inline"
  __STANDALONE
  __WINESRC__
  WINE_UNICODE_NATIVE

  WINE_NO_TRACE_MSGS
  WINE_NO_DEBUG_MSGS
)

add_compile_definitions(
  __STANDALONE__

  ENABLE_OPENGL
  ENABLE_SDL_VIDEO
  ENABLE_SDL_INPUT
  ENABLE_SDL_GAMECONTROLLER
  )

add_library(vpinball SHARED
  ${VPINBALL_SOURCE_DIR}/src/core/def.h
  ${VPINBALL_SOURCE_DIR}/src/parts/dragpoint.cpp
  ${VPINBALL_SOURCE_DIR}/src/utils/eventproxy.h
  ${VPINBALL_SOURCE_DIR}/src/parts/backGlass.cpp
  ${VPINBALL_SOURCE_DIR}/src/core/pininput.cpp
  ${VPINBALL_SOURCE_DIR}/src/core/pininput_OpenPinDev.cpp
  ${VPINBALL_SOURCE_DIR}/src/parts/pinbinary.cpp
  ${VPINBALL_SOURCE_DIR}/src/core/vpversion.h

  ${VPINBALL_SOURCE_DIR}/src/audio/mixer.cpp
  ${VPINBALL_SOURCE_DIR}/src/audio/mixer.h
  ${VPINBALL_SOURCE_DIR}/src/audio/audioplayer.cpp
  ${VPINBALL_SOURCE_DIR}/src/audio/audioplayer.h
  ${VPINBALL_SOURCE_DIR}/src/audio/pinsound.cpp
  ${VPINBALL_SOURCE_DIR}/src/audio/pinsound.h

  ${VPINBALL_SOURCE_DIR}/src/core/dispid.h
  ${VPINBALL_SOURCE_DIR}/src/core/editablereg.h
  ${VPINBALL_SOURCE_DIR}/src/core/editablereg.cpp
  ${VPINBALL_SOURCE_DIR}/src/core/extern.cpp
  ${VPINBALL_SOURCE_DIR}/src/core/extern.h
  ${VPINBALL_SOURCE_DIR}/src/core/ieditable.cpp
  ${VPINBALL_SOURCE_DIR}/src/core/ieditable.h
  ${VPINBALL_SOURCE_DIR}/src/core/iselect.cpp
  ${VPINBALL_SOURCE_DIR}/src/core/iselect.h
  ${VPINBALL_SOURCE_DIR}/src/core/pininput.h
  ${VPINBALL_SOURCE_DIR}/src/core/pinundo.cpp
  ${VPINBALL_SOURCE_DIR}/src/core/pinundo.h
  ${VPINBALL_SOURCE_DIR}/src/core/main.h
  ${VPINBALL_SOURCE_DIR}/src/core/vpinball.cpp
  ${VPINBALL_SOURCE_DIR}/src/core/vpinball_h.h
  ${VPINBALL_SOURCE_DIR}/src/core/player.cpp
  ${VPINBALL_SOURCE_DIR}/src/core/player.h
  ${VPINBALL_SOURCE_DIR}/src/core/Settings.cpp
  ${VPINBALL_SOURCE_DIR}/src/core/Settings.h
  ${VPINBALL_SOURCE_DIR}/src/core/TableDB.cpp
  ${VPINBALL_SOURCE_DIR}/src/core/TableDB.h
  ${VPINBALL_SOURCE_DIR}/src/core/DynamicScript.cpp
  ${VPINBALL_SOURCE_DIR}/src/core/DynamicScript.h

  ${VPINBALL_SOURCE_DIR}/src/math/bbox.h
  ${VPINBALL_SOURCE_DIR}/src/math/math.cpp
  ${VPINBALL_SOURCE_DIR}/src/math/math.h
  ${VPINBALL_SOURCE_DIR}/src/math/matrix.cpp
  ${VPINBALL_SOURCE_DIR}/src/math/matrix.h
  ${VPINBALL_SOURCE_DIR}/src/math/vector.h
  ${VPINBALL_SOURCE_DIR}/src/math/mesh.h
  ${VPINBALL_SOURCE_DIR}/src/math/ModelViewProj.h

  ${VPINBALL_SOURCE_DIR}/src/meshes/ballMesh.h
  ${VPINBALL_SOURCE_DIR}/src/meshes/bulbLightMesh.h
  ${VPINBALL_SOURCE_DIR}/src/meshes/bulbSocketMesh.h
  ${VPINBALL_SOURCE_DIR}/src/meshes/bumperBaseMesh.h
  ${VPINBALL_SOURCE_DIR}/src/meshes/bumperCapMesh.h
  ${VPINBALL_SOURCE_DIR}/src/meshes/bumperRingMesh.h
  ${VPINBALL_SOURCE_DIR}/src/meshes/bumperSocketMesh.h
  ${VPINBALL_SOURCE_DIR}/src/meshes/dropTargetT2Mesh.h
  ${VPINBALL_SOURCE_DIR}/src/meshes/dropTargetT3Mesh.h
  ${VPINBALL_SOURCE_DIR}/src/meshes/dropTargetT4Mesh.h
  ${VPINBALL_SOURCE_DIR}/src/meshes/flipperBase.h
  ${VPINBALL_SOURCE_DIR}/src/meshes/gateBracketMesh.h
  ${VPINBALL_SOURCE_DIR}/src/meshes/gateLongPlateMesh.h
  ${VPINBALL_SOURCE_DIR}/src/meshes/gatePlateMesh.h
  ${VPINBALL_SOURCE_DIR}/src/meshes/gateWireMesh.h
  ${VPINBALL_SOURCE_DIR}/src/meshes/gateWireRectangleMesh.h
  ${VPINBALL_SOURCE_DIR}/src/meshes/hitTargetFatRectangleMesh.h
  ${VPINBALL_SOURCE_DIR}/src/meshes/hitTargetFatSquareMesh.h
  ${VPINBALL_SOURCE_DIR}/src/meshes/hitTargetRectangleMesh.h
  ${VPINBALL_SOURCE_DIR}/src/meshes/hitTargetRoundMesh.h
  ${VPINBALL_SOURCE_DIR}/src/meshes/hitTargetT1SlimMesh.h
  ${VPINBALL_SOURCE_DIR}/src/meshes/hitTargetT2SlimMesh.h
  ${VPINBALL_SOURCE_DIR}/src/meshes/kickerCupMesh.h
  ${VPINBALL_SOURCE_DIR}/src/meshes/kickerHitMesh.h
  ${VPINBALL_SOURCE_DIR}/src/meshes/kickerHoleMesh.h
  ${VPINBALL_SOURCE_DIR}/src/meshes/kickerSimpleHoleMesh.h
  ${VPINBALL_SOURCE_DIR}/src/meshes/spinnerBracketMesh.h
  ${VPINBALL_SOURCE_DIR}/src/meshes/spinnerPlateMesh.h
  ${VPINBALL_SOURCE_DIR}/src/meshes/triggerSimpleMesh.h
  ${VPINBALL_SOURCE_DIR}/src/meshes/triggerStarMesh.h

  ${VPINBALL_SOURCE_DIR}/src/parts/backGlass.h
  ${VPINBALL_SOURCE_DIR}/src/parts/dragpoint.h
  ${VPINBALL_SOURCE_DIR}/src/parts/Material.h
  ${VPINBALL_SOURCE_DIR}/src/parts/pinbinary.h
  ${VPINBALL_SOURCE_DIR}/src/parts/ball.cpp
  ${VPINBALL_SOURCE_DIR}/src/parts/ball.h
  ${VPINBALL_SOURCE_DIR}/src/parts/bumper.cpp
  ${VPINBALL_SOURCE_DIR}/src/parts/bumper.h
  ${VPINBALL_SOURCE_DIR}/src/parts/decal.cpp
  ${VPINBALL_SOURCE_DIR}/src/parts/decal.h
  ${VPINBALL_SOURCE_DIR}/src/parts/dispreel.cpp
  ${VPINBALL_SOURCE_DIR}/src/parts/dispreel.h
  ${VPINBALL_SOURCE_DIR}/src/parts/flasher.cpp
  ${VPINBALL_SOURCE_DIR}/src/parts/flasher.h
  ${VPINBALL_SOURCE_DIR}/src/parts/flipper.cpp
  ${VPINBALL_SOURCE_DIR}/src/parts/flipper.h
  ${VPINBALL_SOURCE_DIR}/src/parts/gate.cpp
  ${VPINBALL_SOURCE_DIR}/src/parts/gate.h
  ${VPINBALL_SOURCE_DIR}/src/parts/hittarget.cpp
  ${VPINBALL_SOURCE_DIR}/src/parts/hittarget.h
  ${VPINBALL_SOURCE_DIR}/src/parts/kicker.cpp
  ${VPINBALL_SOURCE_DIR}/src/parts/kicker.h
  ${VPINBALL_SOURCE_DIR}/src/parts/light.cpp
  ${VPINBALL_SOURCE_DIR}/src/parts/light.h
  ${VPINBALL_SOURCE_DIR}/src/parts/lightseq.cpp
  ${VPINBALL_SOURCE_DIR}/src/parts/lightseq.h
  ${VPINBALL_SOURCE_DIR}/src/parts/pintable.cpp
  ${VPINBALL_SOURCE_DIR}/src/parts/pintable.h
  ${VPINBALL_SOURCE_DIR}/src/parts/plunger.cpp
  ${VPINBALL_SOURCE_DIR}/src/parts/plunger.h
  ${VPINBALL_SOURCE_DIR}/src/parts/primitive.cpp
  ${VPINBALL_SOURCE_DIR}/src/parts/primitive.h
  ${VPINBALL_SOURCE_DIR}/src/parts/ramp.cpp
  ${VPINBALL_SOURCE_DIR}/src/parts/ramp.h
  ${VPINBALL_SOURCE_DIR}/src/parts/rubber.h
  ${VPINBALL_SOURCE_DIR}/src/parts/rubber.cpp
  ${VPINBALL_SOURCE_DIR}/src/parts/spinner.cpp
  ${VPINBALL_SOURCE_DIR}/src/parts/spinner.h
  ${VPINBALL_SOURCE_DIR}/src/parts/surface.cpp
  ${VPINBALL_SOURCE_DIR}/src/parts/surface.h
  ${VPINBALL_SOURCE_DIR}/src/parts/textbox.cpp
  ${VPINBALL_SOURCE_DIR}/src/parts/textbox.h
  ${VPINBALL_SOURCE_DIR}/src/parts/timer.cpp
  ${VPINBALL_SOURCE_DIR}/src/parts/timer.h
  ${VPINBALL_SOURCE_DIR}/src/parts/trigger.cpp
  ${VPINBALL_SOURCE_DIR}/src/parts/trigger.h

  ${VPINBALL_SOURCE_DIR}/src/physics/physconst.h
  ${VPINBALL_SOURCE_DIR}/src/physics/collide.cpp
  ${VPINBALL_SOURCE_DIR}/src/physics/collide.h
  ${VPINBALL_SOURCE_DIR}/src/physics/collideex.cpp
  ${VPINBALL_SOURCE_DIR}/src/physics/collideex.h
  ${VPINBALL_SOURCE_DIR}/src/physics/hitable.h
  ${VPINBALL_SOURCE_DIR}/src/physics/hitball.cpp
  ${VPINBALL_SOURCE_DIR}/src/physics/hitball.h
  ${VPINBALL_SOURCE_DIR}/src/physics/hitflipper.cpp
  ${VPINBALL_SOURCE_DIR}/src/physics/hitflipper.h
  ${VPINBALL_SOURCE_DIR}/src/physics/hitplunger.cpp
  ${VPINBALL_SOURCE_DIR}/src/physics/hitplunger.h
  ${VPINBALL_SOURCE_DIR}/src/physics/hittimer.h
  ${VPINBALL_SOURCE_DIR}/src/physics/kdtree.cpp
  ${VPINBALL_SOURCE_DIR}/src/physics/kdtree.h
  ${VPINBALL_SOURCE_DIR}/src/physics/NudgeFilter.cpp
  ${VPINBALL_SOURCE_DIR}/src/physics/NudgeFilter.h
  ${VPINBALL_SOURCE_DIR}/src/physics/PhysicsEngine.cpp
  ${VPINBALL_SOURCE_DIR}/src/physics/PhysicsEngine.h
  ${VPINBALL_SOURCE_DIR}/src/physics/quadtree.cpp
  ${VPINBALL_SOURCE_DIR}/src/physics/quadtree.h

  ${VPINBALL_SOURCE_DIR}/src/plugins/MsgPlugin.h
  ${VPINBALL_SOURCE_DIR}/src/plugins/MsgPluginManager.h
  ${VPINBALL_SOURCE_DIR}/src/plugins/MsgPluginManager.cpp
  ${VPINBALL_SOURCE_DIR}/src/plugins/VPXPluginAPIImpl.h
  ${VPINBALL_SOURCE_DIR}/src/plugins/VPXPluginAPIImpl.cpp
  ${VPINBALL_SOURCE_DIR}/src/plugins/VPXPlugin.h

  ${VPINBALL_SOURCE_DIR}/src/renderer/trace.h
  ${VPINBALL_SOURCE_DIR}/src/renderer/Anaglyph.cpp
  ${VPINBALL_SOURCE_DIR}/src/renderer/Anaglyph.h
  ${VPINBALL_SOURCE_DIR}/src/renderer/IndexBuffer.cpp
  ${VPINBALL_SOURCE_DIR}/src/renderer/IndexBuffer.h
  ${VPINBALL_SOURCE_DIR}/src/renderer/MeshBuffer.cpp
  ${VPINBALL_SOURCE_DIR}/src/renderer/MeshBuffer.h
  ${VPINBALL_SOURCE_DIR}/src/renderer/Renderable.h
  ${VPINBALL_SOURCE_DIR}/src/renderer/Renderer.cpp
  ${VPINBALL_SOURCE_DIR}/src/renderer/Renderer.h
  ${VPINBALL_SOURCE_DIR}/src/renderer/RenderDevice.cpp
  ${VPINBALL_SOURCE_DIR}/src/renderer/RenderDevice.h
  ${VPINBALL_SOURCE_DIR}/src/renderer/RenderCommand.cpp
  ${VPINBALL_SOURCE_DIR}/src/renderer/RenderCommand.h
  ${VPINBALL_SOURCE_DIR}/src/renderer/RenderFrame.cpp
  ${VPINBALL_SOURCE_DIR}/src/renderer/RenderFrame.h
  ${VPINBALL_SOURCE_DIR}/src/renderer/RenderPass.cpp
  ${VPINBALL_SOURCE_DIR}/src/renderer/RenderPass.h
  ${VPINBALL_SOURCE_DIR}/src/renderer/RenderProbe.cpp
  ${VPINBALL_SOURCE_DIR}/src/renderer/RenderProbe.h
  ${VPINBALL_SOURCE_DIR}/src/renderer/RenderState.cpp
  ${VPINBALL_SOURCE_DIR}/src/renderer/RenderState.h
  ${VPINBALL_SOURCE_DIR}/src/renderer/RenderTarget.cpp
  ${VPINBALL_SOURCE_DIR}/src/renderer/RenderTarget.h
  ${VPINBALL_SOURCE_DIR}/src/renderer/Sampler.cpp
  ${VPINBALL_SOURCE_DIR}/src/renderer/Sampler.h
  ${VPINBALL_SOURCE_DIR}/src/renderer/Shader.cpp
  ${VPINBALL_SOURCE_DIR}/src/renderer/Shader.h
  ${VPINBALL_SOURCE_DIR}/src/renderer/Texture.cpp
  ${VPINBALL_SOURCE_DIR}/src/renderer/Texture.h
  ${VPINBALL_SOURCE_DIR}/src/renderer/TextureManager.cpp
  ${VPINBALL_SOURCE_DIR}/src/renderer/TextureManager.h
  ${VPINBALL_SOURCE_DIR}/src/renderer/VertexBuffer.cpp
  ${VPINBALL_SOURCE_DIR}/src/renderer/VertexBuffer.h
  ${VPINBALL_SOURCE_DIR}/src/renderer/ViewSetup.cpp
  ${VPINBALL_SOURCE_DIR}/src/renderer/ViewSetup.h
  ${VPINBALL_SOURCE_DIR}/src/renderer/VRDevice.cpp
  ${VPINBALL_SOURCE_DIR}/src/renderer/VRDevice.h
  ${VPINBALL_SOURCE_DIR}/src/renderer/Window.cpp
  ${VPINBALL_SOURCE_DIR}/src/renderer/Window.h

  ${VPINBALL_SOURCE_DIR}/src/ui/codeview.cpp
  ${VPINBALL_SOURCE_DIR}/src/ui/codeview.h
  ${VPINBALL_SOURCE_DIR}/src/ui/codeviewedit.cpp
  ${VPINBALL_SOURCE_DIR}/src/ui/codeviewedit.h
  ${VPINBALL_SOURCE_DIR}/src/ui/LiveUI.cpp
  ${VPINBALL_SOURCE_DIR}/src/ui/LiveUI.h
  ${VPINBALL_SOURCE_DIR}/src/ui/hitrectsur.cpp
  ${VPINBALL_SOURCE_DIR}/src/ui/hitrectsur.h
  ${VPINBALL_SOURCE_DIR}/src/ui/hitsur.cpp
  ${VPINBALL_SOURCE_DIR}/src/ui/hitsur.h

  ${VPINBALL_SOURCE_DIR}/src/utils/bulb.cpp
  ${VPINBALL_SOURCE_DIR}/src/utils/bulb.h
  ${VPINBALL_SOURCE_DIR}/src/utils/def.cpp
  ${VPINBALL_SOURCE_DIR}/src/utils/wintimer.cpp
  ${VPINBALL_SOURCE_DIR}/src/utils/wintimer.h
  ${VPINBALL_SOURCE_DIR}/src/utils/helpers.h
  ${VPINBALL_SOURCE_DIR}/src/utils/ushock_output.cpp
  ${VPINBALL_SOURCE_DIR}/src/utils/ushock_output.h
  ${VPINBALL_SOURCE_DIR}/src/utils/variant.cpp
  ${VPINBALL_SOURCE_DIR}/src/utils/variant.h
  ${VPINBALL_SOURCE_DIR}/src/utils/vector.h
  ${VPINBALL_SOURCE_DIR}/src/utils/vectorsort.h
  ${VPINBALL_SOURCE_DIR}/src/utils/fileio.cpp
  ${VPINBALL_SOURCE_DIR}/src/utils/fileio.h
  ${VPINBALL_SOURCE_DIR}/src/utils/lzwreader.cpp
  ${VPINBALL_SOURCE_DIR}/src/utils/lzwreader.h
  ${VPINBALL_SOURCE_DIR}/src/utils/lzwwriter.cpp
  ${VPINBALL_SOURCE_DIR}/src/utils/lzwwriter.h
  ${VPINBALL_SOURCE_DIR}/src/utils/hash.cpp
  ${VPINBALL_SOURCE_DIR}/src/utils/hash.h
  ${VPINBALL_SOURCE_DIR}/src/utils/objloader.cpp
  ${VPINBALL_SOURCE_DIR}/src/utils/objloader.h
  ${VPINBALL_SOURCE_DIR}/src/utils/Logger.cpp
  ${VPINBALL_SOURCE_DIR}/src/utils/Logger.h

  ${VPINBALL_SOURCE_DIR}/third-party/include/hidapi/hidapi.h
  ${VPINBALL_SOURCE_DIR}/third-party/include/hid-report-parser/hid_report_parser.cpp
  ${VPINBALL_SOURCE_DIR}/third-party/include/hid-report-parser/hid_report_parser.h
  ${VPINBALL_SOURCE_DIR}/third-party/include/imgui/imconfig.h
  ${VPINBALL_SOURCE_DIR}/third-party/include/imgui/imgui.cpp
  ${VPINBALL_SOURCE_DIR}/third-party/include/imgui/imgui.h
  ${VPINBALL_SOURCE_DIR}/third-party/include/imgui/imgui_draw.cpp
  ${VPINBALL_SOURCE_DIR}/third-party/include/imgui/imgui_impl_opengl3.cpp
  ${VPINBALL_SOURCE_DIR}/third-party/include/imgui/imgui_impl_opengl3.h
  ${VPINBALL_SOURCE_DIR}/third-party/include/imgui/imgui_impl_sdl3.cpp
  ${VPINBALL_SOURCE_DIR}/third-party/include/imgui/imgui_impl_sdl3.h
  ${VPINBALL_SOURCE_DIR}/third-party/include/imgui/imgui_stdlib.cpp
  ${VPINBALL_SOURCE_DIR}/third-party/include/imgui/imgui_stdlib.h
  ${VPINBALL_SOURCE_DIR}/third-party/include/imgui/imgui_tables.cpp
  ${VPINBALL_SOURCE_DIR}/third-party/include/imgui/imgui_widgets.cpp
  ${VPINBALL_SOURCE_DIR}/third-party/include/imgui/imgui_internal.h
  ${VPINBALL_SOURCE_DIR}/third-party/include/imguizmo/ImGuizmo.cpp
  ${VPINBALL_SOURCE_DIR}/third-party/include/imguizmo/ImGuizmo.h
  ${VPINBALL_SOURCE_DIR}/third-party/include/implot/implot.cpp
  ${VPINBALL_SOURCE_DIR}/third-party/include/implot/implot.h
  ${VPINBALL_SOURCE_DIR}/third-party/include/implot/implot_items.cpp
  ${VPINBALL_SOURCE_DIR}/third-party/include/implot/implot_internal.h
  ${VPINBALL_SOURCE_DIR}/third-party/include/gpuprofiler.cpp
  ${VPINBALL_SOURCE_DIR}/third-party/include/gpuprofiler.h
  ${VPINBALL_SOURCE_DIR}/third-party/include/progmesh.cpp
  ${VPINBALL_SOURCE_DIR}/third-party/include/progmesh.h
  ${VPINBALL_SOURCE_DIR}/third-party/include/ThreadPool.h
  ${VPINBALL_SOURCE_DIR}/third-party/include/mINI/ini.h
  ${VPINBALL_SOURCE_DIR}/third-party/include/tinyxml2/tinyxml2.cpp
  ${VPINBALL_SOURCE_DIR}/third-party/include/tinyxml2/tinyxml2.h
  ${VPINBALL_SOURCE_DIR}/third-party/include/miniz/miniz.c
  ${VPINBALL_SOURCE_DIR}/third-party/include/miniz/miniz.h   
  ${VPINBALL_SOURCE_DIR}/third-party/include/robin_hood.h
  ${VPINBALL_SOURCE_DIR}/third-party/include/RSJparser/RSJparser.tcc

  ${VPINBALL_SOURCE_DIR}/standalone/vpinball_standalone_i.c
  ${VPINBALL_SOURCE_DIR}/standalone/vpinball_standalone_i.h
  ${VPINBALL_SOURCE_DIR}/standalone/vpinball_standalone_i_proxy.cpp

  ${VPINBALL_SOURCE_DIR}/standalone/inc/webserver/mongoose.c
  ${VPINBALL_SOURCE_DIR}/standalone/inc/webserver/mongoose.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/webserver/WebServer.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/webserver/WebServer.h

  ${VPINBALL_SOURCE_DIR}/standalone/inc/pole/pole.cpp

  ${VPINBALL_SOURCE_DIR}/standalone/PoleStream.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/PoleStorage.cpp

  ${VPINBALL_SOURCE_DIR}/standalone/inc/vpinmame/VPinMAMEController.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/vpinmame/VPinMAMEController.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/vpinmame/VPinMAMEControllerSettings.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/vpinmame/VPinMAMEControllerSettings.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/vpinmame/VPinMAMEGame.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/vpinmame/VPinMAMEGame.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/vpinmame/VPinMAMEGames.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/vpinmame/VPinMAMEGames.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/vpinmame/VPinMAMEGameSettings.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/vpinmame/VPinMAMEGameSettings.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/vpinmame/VPinMAMERom.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/vpinmame/VPinMAMERom.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/vpinmame/VPinMAMERoms.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/vpinmame/VPinMAMERoms.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/vpinmame/vpinmame_i_proxy.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/vpinmame/vpinmame_i.c
  ${VPINBALL_SOURCE_DIR}/standalone/inc/vpinmame/vpinmame_i.h

  ${VPINBALL_SOURCE_DIR}/standalone/inc/wmp/WMPCore.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/wmp/WMPCore.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/wmp/WMPControls.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/wmp/WMPControls.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/wmp/WMPSettings.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/wmp/WMPSettings.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/wmp/wmp_i_proxy.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/wmp/wmp_i.c
  ${VPINBALL_SOURCE_DIR}/standalone/inc/wmp/wmp_i.h

  ${VPINBALL_SOURCE_DIR}/standalone/inc/ultradmd/UltraDMDDMDObject.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/ultradmd/UltraDMDDMDObject.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/ultradmd/ultradmd_i_proxy.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/ultradmd/ultradmd_i.c
  ${VPINBALL_SOURCE_DIR}/standalone/inc/ultradmd/ultradmd_i.h

  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actions/ActionFactory.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actions/ActionFactory.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actions/Action.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actions/Action.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actions/RepeatAction.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actions/RepeatAction.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actions/SequenceAction.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actions/SequenceAction.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actions/ParallelAction.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actions/ParallelAction.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actions/ShowAction.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actions/ShowAction.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actions/BlinkAction.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actions/BlinkAction.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actions/AddToAction.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actions/AddToAction.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actions/RemoveFromParentAction.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actions/RemoveFromParentAction.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actions/AddChildAction.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actions/AddChildAction.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actions/SeekAction.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actions/SeekAction.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actions/WaitAction.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actions/WaitAction.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actions/DelayedAction.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actions/DelayedAction.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actions/TweenAction.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actions/TweenAction.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actions/MoveToAction.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actions/MoveToAction.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actors/Actor.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actors/Actor.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actors/AnimatedActor.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actors/AnimatedActor.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actors/ImageSequence.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actors/ImageSequence.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actors/GIFImage.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actors/GIFImage.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actors/Font.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actors/Font.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actors/Frame.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actors/Frame.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actors/FadeOverlay.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actors/FadeOverlay.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actors/Group.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actors/Group.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actors/Image.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actors/Image.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actors/Label.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actors/Label.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actors/Video.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actors/Video.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/filters/BitmapFilter.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/filters/BitmapFilter.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/filters/RegionFilter.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/filters/RegionFilter.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/filters/PadFilter.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/filters/PadFilter.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/filters/DotFilter.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/filters/DotFilter.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/filters/AdditiveFilter.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/filters/AdditiveFilter.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/FlexDMD.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/FlexDMD.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/AssetSrc.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/AssetSrc.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/AssetManager.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/AssetManager.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/Bitmap.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/Bitmap.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/Layout.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/Layout.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/UltraDMD.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/UltraDMD.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/FontDef.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/FontDef.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/ImageSequenceDef.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/ImageSequenceDef.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/VideoDef.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/VideoDef.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actors/ScoreBoard.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/actors/ScoreBoard.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/scenes/AnimationType.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/scenes/Scene.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/scenes/Scene.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/scenes/Sequence.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/scenes/Sequence.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/scenes/SingleLineScene.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/scenes/SingleLineScene.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/scenes/TwoLineScene.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/scenes/TwoLineScene.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/scenes/BackgroundScene.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/scenes/BackgroundScene.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/scenes/ScrollingCreditsScene.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/scenes/ScrollingCreditsScene.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/flexudmd_i_proxy.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/flexudmd_i.c
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/flexudmd_i.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/flexdmd_i_proxy.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/flexdmd_i.c
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/flexdmd_i.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/bmfonts/BitmapFont.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/bmfonts/BitmapFont.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/bmfonts/Character.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/bmfonts/Character.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/bmfonts/Kerning.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/bmfonts/Kerning.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/bmfonts/Page.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/bmfonts/Page.h

  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/classes/AnimationInfo.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/classes/AnimationInfo.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/classes/B2SAnimation.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/classes/B2SAnimation.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/classes/B2SAnimationBase.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/classes/B2SAnimationBase.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/classes/B2SCollectData.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/classes/B2SCollectData.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/classes/B2SData.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/classes/B2SData.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/classes/B2SPlayer.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/classes/B2SPlayer.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/classes/B2SScreen.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/classes/B2SScreen.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/classes/B2SSettings.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/classes/B2SSettings.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/classes/B2SReelDisplay.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/classes/B2SReelDisplay.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/classes/CollectData.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/classes/CollectData.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/classes/ControlInfo.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/classes/ControlInfo.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/classes/EntryAction.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/classes/EntryAction.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/classes/LEDAreaInfo.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/classes/LEDAreaInfo.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/classes/LEDDisplayDigitLocation.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/classes/LEDDisplayDigitLocation.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/classes/PictureBoxAnimation.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/classes/PictureBoxAnimation.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/classes/PictureBoxAnimationEntry.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/classes/PictureBoxAnimationEntry.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/classes/Sound.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/classes/Sound.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/collections/AnimationCollection.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/collections/AnimationCollection.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/collections/ControlCollection.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/collections/ControlCollection.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/collections/GenericDictionaryIgnoreCase.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/collections/GenericDictionaryIgnoreCase.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/collections/IlluminationGroupCollection.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/collections/IlluminationGroupCollection.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/collections/PictureBoxCollection.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/collections/PictureBoxCollection.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/collections/ReelDisplayReelBoxCollection.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/collections/ReelDisplayReelBoxCollection.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/collections/ReelBoxCollection.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/collections/ReelBoxCollection.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/collections/RunningAnimationsCollection.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/collections/RunningAnimationsCollection.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/collections/ZOrderCollection.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/collections/ZOrderCollection.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/controls/B2SBaseBox.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/controls/B2SBaseBox.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/controls/B2SLEDBox.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/controls/B2SLEDBox.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/controls/B2SPictureBox.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/controls/B2SPictureBox.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/controls/B2SReelBox.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/controls/B2SReelBox.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/controls/Control.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/controls/Control.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/dream7/Dream7Display.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/dream7/Dream7Display.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/dream7/Segment.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/dream7/Segment.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/dream7/SegmentList.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/dream7/SegmentList.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/dream7/SegmentNumber.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/dream7/SegmentNumber.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/dream7/SegmentStyle.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/dream7/SegmentStyle.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/forms/FormWindow.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/forms/FormWindow.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/forms/Form.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/forms/Form.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/forms/FormBackglass.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/forms/FormBackglass.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/forms/FormDMD.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/forms/FormDMD.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/plugin/Plugin.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/plugin/Plugin.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/plugin/PluginHost.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/plugin/PluginHost.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/Server.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/Server.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/b2s_i_proxy.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/b2s_i.c
  ${VPINBALL_SOURCE_DIR}/standalone/inc/b2s/b2s_i.h

  ${VPINBALL_SOURCE_DIR}/standalone/inc/dof/DOFPlugin.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/dof/DOFPlugin.h

  ${VPINBALL_SOURCE_DIR}/standalone/Standalone.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/Standalone.h

  ${VPINBALL_SOURCE_DIR}/standalone/inc/pup/PUPManager.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/pup/PUPManager.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/pup/PUPPinDisplay.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/pup/PUPPinDisplay.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/pup/PUPPlaylist.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/pup/PUPPlaylist.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/pup/PUPTrigger.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/pup/PUPTrigger.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/pup/PUPScreen.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/pup/PUPScreen.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/pup/PUPLabel.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/pup/PUPLabel.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/pup/PUPCustomPos.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/pup/PUPCustomPos.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/pup/PUPPlugin.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/pup/PUPPlugin.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/pup/PUPWindow.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/pup/PUPWindow.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/pup/PUPMediaPlayer.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/pup/PUPMediaPlayer.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/pup/PUPMediaManager.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/pup/PUPMediaManager.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/pup/pup_i_proxy.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/pup/pup_i.c
  ${VPINBALL_SOURCE_DIR}/standalone/inc/pup/pup_i.h

  ${VPINBALL_SOURCE_DIR}/standalone/inc/common/WindowManager.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/common/WindowManager.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/common/Window.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/common/Window.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/common/DMDWindow.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/common/DMDWindow.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/common/RendererGraphics.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/common/RendererGraphics.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/common/SurfaceGraphics.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/common/SurfaceGraphics.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/common/GraphicsPath.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/common/GraphicsPath.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/common/Matrix.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/common/Matrix.h
  ${VPINBALL_SOURCE_DIR}/standalone/inc/common/Timer.cpp
  ${VPINBALL_SOURCE_DIR}/standalone/inc/common/Timer.h
)

target_include_directories(vpinball PUBLIC
   ${VPINBALL_SOURCE_DIR}/standalone/linux-x64/external/include
   ${VPINBALL_SOURCE_DIR}
   ${VPINBALL_SOURCE_DIR}/third-party/include
   ${VPINBALL_SOURCE_DIR}/standalone/inc/pole
   ${VPINBALL_SOURCE_DIR}/media
   ${VPINBALL_SOURCE_DIR}/pin
   ${VPINBALL_SOURCE_DIR}/src
)

target_compile_definitions( 
  vpinball PUBLIC
   "-D__forceinline=__attribute__((always_inline)) inline" 
)

target_precompile_headers(vpinball PUBLIC
)

target_compile_options(vpinball PUBLIC
   -mssse3
   # XXX: removed to allow VPinball to be built as library
   # -fvisibility=hidden
   $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:
      -fdenormal-fp-math=preserve-sign
      -freciprocal-math
      -fassociative-math
      -fapprox-func
      -fno-math-errno
      -fno-trapping-math
      -ffp-contract=off
      -Wno-shorten-64-to-32>
   $<$<CXX_COMPILER_ID:GNU>:
      -ffast-math
      -ffp-contract=off>
)

target_link_directories(vpinball PUBLIC
   ${VPINBALL_SOURCE_DIR}/standalone/linux-x64/external/lib
)

target_link_libraries(vpinball PUBLIC
   glad
   SDL3
   SDL3_image
   SDL3_ttf
   freeimage
   bass
   hidapi-hidraw
   pinmame
   altsound
   dmdutil
   dof
   avcodec
   avdevice
   avfilter
   avformat
   avutil
   swresample
   swscale
   wine
)

set_target_properties(vpinball PROPERTIES
  LINK_FLAGS "-Wl,--copy-dt-needed-entries"
)

# XXX: Artifacts from the original CMakeFile. I'm not sure we need this.
# add_custom_command(TARGET vpinball POST_BUILD
#    COMMAND "${CMAKE_COMMAND}" -E make_directory "$<TARGET_FILE_DIR:vpinball>/user"
#    COMMAND "${CMAKE_COMMAND}" -E copy_directory "${VPINBALL_SOURCE_DIR}/src/assets" "$<TARGET_FILE_DIR:vpinball>/assets"
#    COMMAND "${CMAKE_COMMAND}" -E copy_directory "${VPINBALL_SOURCE_DIR}/scripts" "$<TARGET_FILE_DIR:vpinball>/scripts"
#    COMMAND "${CMAKE_COMMAND}" -E copy_directory "${VPINBALL_SOURCE_DIR}/tables" "$<TARGET_FILE_DIR:vpinball>/tables"
#    COMMAND "${CMAKE_COMMAND}" -E copy_directory "${VPINBALL_SOURCE_DIR}/docs" "$<TARGET_FILE_DIR:vpinball>/docs"
#    COMMAND "${CMAKE_COMMAND}" -E make_directory "$<TARGET_FILE_DIR:vpinball>/shaders-${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_REV}"
#    COMMAND "${CMAKE_COMMAND}" -E copy "${VPINBALL_SOURCE_DIR}/src/shaders/hlsl_glsl/BasicShader.glfx" "$<TARGET_FILE_DIR:vpinball>/shaders-${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_REV}"
#    COMMAND "${CMAKE_COMMAND}" -E copy "${VPINBALL_SOURCE_DIR}/src/shaders/hlsl_glsl/DMDShader.glfx" "$<TARGET_FILE_DIR:vpinball>/shaders-${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_REV}"
#    COMMAND "${CMAKE_COMMAND}" -E copy "${VPINBALL_SOURCE_DIR}/src/shaders/hlsl_glsl/FBShader.glfx" "$<TARGET_FILE_DIR:vpinball>/shaders-${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_REV}"
#    COMMAND "${CMAKE_COMMAND}" -E copy "${VPINBALL_SOURCE_DIR}/src/shaders/hlsl_glsl/SMAA.glfx" "$<TARGET_FILE_DIR:vpinball>/shaders-${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_REV}"  
#    COMMAND "${CMAKE_COMMAND}" -E copy "${VPINBALL_SOURCE_DIR}/src/shaders/hlsl_glsl/FlasherShader.glfx" "$<TARGET_FILE_DIR:vpinball>/shaders-${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_REV}"
#    COMMAND "${CMAKE_COMMAND}" -E copy "${VPINBALL_SOURCE_DIR}/src/shaders/hlsl_glsl/LightShader.glfx" "$<TARGET_FILE_DIR:vpinball>/shaders-${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_REV}"
#    COMMAND "${CMAKE_COMMAND}" -E copy "${VPINBALL_SOURCE_DIR}/src/shaders/hlsl_glsl/BallShader.glfx" "$<TARGET_FILE_DIR:vpinball>/shaders-${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_REV}"
#    COMMAND "${CMAKE_COMMAND}" -E copy "${VPINBALL_SOURCE_DIR}/src/shaders/hlsl_glsl/ClassicLightShader.glfx" "$<TARGET_FILE_DIR:vpinball>/shaders-${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_REV}"
#    COMMAND "${CMAKE_COMMAND}" -E copy "${VPINBALL_SOURCE_DIR}/src/shaders/hlsl_glsl/StereoShader.glfx" "$<TARGET_FILE_DIR:vpinball>/shaders-${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_REV}"
#    COMMAND "${CMAKE_COMMAND}" -E copy "${VPINBALL_SOURCE_DIR}/src/shaders/hlsl_glsl/Helpers.fxh" "$<TARGET_FILE_DIR:vpinball>/shaders-${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_REV}"
#    COMMAND "${CMAKE_COMMAND}" -E copy "${VPINBALL_SOURCE_DIR}/src/shaders/hlsl_glsl/FBShader.fxh" "$<TARGET_FILE_DIR:vpinball>/shaders-${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_REV}"
#    COMMAND "${CMAKE_COMMAND}" -E copy "${VPINBALL_SOURCE_DIR}/src/shaders/hlsl_glsl/Material_GL.fxh" "$<TARGET_FILE_DIR:vpinball>/shaders-${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_REV}"
#    COMMAND "${CMAKE_COMMAND}" -E copy "${VPINBALL_SOURCE_DIR}/src/shaders/hlsl_glsl/BallShadows.fxh" "$<TARGET_FILE_DIR:vpinball>/shaders-${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_REV}"
#    COMMAND "${CMAKE_COMMAND}" -E copy "${VPINBALL_SOURCE_DIR}/src/shaders/hlsl_glsl/SMAA.fxh" "$<TARGET_FILE_DIR:vpinball>/shaders-${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_REV}"
#    COMMAND "${CMAKE_COMMAND}" -E copy "${VPINBALL_SOURCE_DIR}/src/shaders/hlsl_glsl/FXAAStereoAO_GL.fxh" "$<TARGET_FILE_DIR:vpinball>/shaders-${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_REV}"
#    COMMAND "${CMAKE_COMMAND}" -E copy "${VPINBALL_SOURCE_DIR}/src/shaders/hlsl_glsl/SSR_GL.fxh" "$<TARGET_FILE_DIR:vpinball>/shaders-${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_REV}"
#    COMMAND "${CMAKE_COMMAND}" -E copy "${VPINBALL_SOURCE_DIR}/src/shaders/hlsl_glsl/Stereo.fxh" "$<TARGET_FILE_DIR:vpinball>/shaders-${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_REV}"
#    COMMAND "${CMAKE_COMMAND}" -E copy_directory "${VPINBALL_SOURCE_DIR}/standalone/inc/flexdmd/resources" "$<TARGET_FILE_DIR:vpinball>/flexdmd"
# )

add_custom_command(TARGET vpinball POST_BUILD
  COMMAND cp -a "${VPINBALL_SOURCE_DIR}/standalone/linux-x64/external/lib/*.so" "$<TARGET_FILE_DIR:vpinball>"
  COMMAND cp -a "${VPINBALL_SOURCE_DIR}/standalone/linux-x64/external/lib/*.so.*" "$<TARGET_FILE_DIR:vpinball>"
)


# This is the adapter public target to link to
add_library(adapter_vpinball SHARED
  units.cpp
  CWDGuard.cpp
  VPinBumper.cpp
  VPinTable.cpp
  VPinTableElement.cpp
  VPinballAdapter.cpp
)

target_compile_features(adapter_vpinball PUBLIC cxx_std_20)

target_include_directories(adapter_vpinball PUBLIC include)

target_link_libraries(adapter_vpinball
  PRIVATE vpinball
  PUBLIC adapter_interface
)

add_library(adapter::vpinball ALIAS adapter_vpinball)
