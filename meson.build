project('XCSoar',
    ['c', 'cpp'],
    version: '7.0_preview12',
    meson_version: '>= 0.47.2',
    default_options: [
        'c_std=c99',
        'cpp_std=c++14'
    ],
    license: 'GPL-2.0'
)

compiler = meson.get_compiler('cpp')
c_compiler = meson.get_compiler('c')

common_cppflags = [
  '-D_GNU_SOURCE',
]

common_cflags = [
]

common_cxxflags = [
]

add_global_arguments(common_cppflags, language: 'c')
add_global_arguments(common_cppflags, language: 'cpp')

conf = configuration_data()
conf.set_quoted('PACKAGE', meson.project_name())
conf.set_quoted('PACKAGE_NAME', meson.project_name())
conf.set_quoted('PACKAGE_VERSION', meson.project_version())
conf.set_quoted('VERSION', meson.project_version())

is_linux = host_machine.system() == 'linux'
is_darwin = host_machine.system() == 'darwin'
is_windows = host_machine.system() == 'windows'
is_android = false #get_option('android_ndk') != ''

if is_windows
  subdir('win32')
endif

if is_android
  subdir('android')
endif

inc = include_directories(
  'src'
)

sources = [
    'src/LibCXX.cpp',
    'src/Compatibility/fmode.c',
    'src/Apple/InternalSensors.cpp'
]

subdir('src/Airspace')
if is_android
    subdir('src/Android')
endif
subdir('src/Atmosphere')
subdir('src/Audio')
subdir('src/Blackboard')
subdir('src/Cloud')
subdir('src/Computer')
subdir('src/Config')
subdir('src/CrossSection')
subdir('src/Device')
subdir('src/Device/Driver')
subdir('src/Device/Driver/BlueFly')
subdir('src/Device/Driver/CAI302')
subdir('src/Device/Driver/FLARM')
subdir('src/Device/Driver/Flytec')
subdir('src/Device/Driver/IMI')
subdir('src/Device/Driver/IMI/Protocol')
subdir('src/Device/Driver/LX')
subdir('src/Device/Driver/ThermalExpress')
subdir('src/Device/Driver/Vega')
subdir('src/Device/Driver/Volkslogger')
subdir('src/Device/Driver/XCTracer')
subdir('src/Device/Port')
subdir('src/Device/Util')
subdir('src/Dialogs')
subdir('src/Dialogs/Airspace')
subdir('src/Dialogs/Device')
subdir('src/Dialogs/Device/BlueFly')
subdir('src/Dialogs/Device/CAI302')
subdir('src/Dialogs/Device/FLARM')
subdir('src/Dialogs/Device/LX')
subdir('src/Dialogs/Device/Vega')
subdir('src/Dialogs/Plane')
subdir('src/Dialogs/Settings')
subdir('src/Dialogs/Settings/Panels')
subdir('src/Dialogs/StatusPanels')
subdir('src/Dialogs/Task')
subdir('src/Dialogs/Task/Manager')
subdir('src/Dialogs/Task/Widgets')
subdir('src/Dialogs/Tracking')
subdir('src/Dialogs/Traffic')
subdir('src/Dialogs/Waypoint')
subdir('src/Dialogs/Weather')
subdir('src/Engine')
subdir('src/Engine/Airspace')
subdir('src/Engine/Airspace/Predicate')
subdir('src/Engine/Contest')
subdir('src/Engine/Contest/Solvers')
subdir('src/Engine/GlideSolvers')
subdir('src/Engine/Navigation')
subdir('src/Engine/PathSolvers')
subdir('src/Engine/Route')
subdir('src/Engine/Task')
subdir('src/Engine/Task/Computer')
subdir('src/Engine/Task/Factory')
subdir('src/Engine/Task/ObservationZones')
subdir('src/Engine/Task/Ordered')
subdir('src/Engine/Task/Ordered/Points')
subdir('src/Engine/Task/PathSolvers')
subdir('src/Engine/Task/Points')
subdir('src/Engine/Task/Shapes')
subdir('src/Engine/Task/Solvers')
subdir('src/Engine/Task/Stats')
subdir('src/Engine/Task/Unordered')
subdir('src/Engine/Task/Visitors')
subdir('src/Engine/ThermalBand')
subdir('src/Engine/Trace')
subdir('src/Engine/Util')
subdir('src/Engine/Waypoint')
subdir('src/Event')
subdir('src/Event/Android')
subdir('src/Event/Poll')
subdir('src/Event/Poll/LibInput')
subdir('src/Event/Poll/Linux')
subdir('src/Event/SDL')
subdir('src/Event/Shared')
subdir('src/Event/Windows')
subdir('src/FLARM')
subdir('src/Form')
subdir('src/Form/DataField')
subdir('src/Formatter')
subdir('src/Gauge')
subdir('src/Geo')
subdir('src/Geo/Boost')
subdir('src/Geo/ConvexHull')
subdir('src/Geo/Flat')
subdir('src/Geo/Memento')
subdir('src/Hardware')
subdir('src/IGC')
subdir('src/InfoBoxes')
subdir('src/InfoBoxes/Content')
subdir('src/InfoBoxes/Panel')
subdir('src/Input')
subdir('src/IO')
subdir('src/IO/Async')
subdir('src/Java')
subdir('src/Job')
subdir('src/JSON')
subdir('src/Kobo')
subdir('src/Language')
subdir('src/Logger')
subdir('src/Look')
subdir('src/Lua')
subdir('src/MapWindow')
subdir('src/MapWindow/Items')
subdir('src/Markers')
subdir('src/Math')
subdir('src/Math/Boost')
subdir('src/Menu')
subdir('src/Monitor')
subdir('src/Net')
subdir('src/Net/HTTP')
subdir('src/NMEA')
subdir('src/Operation')
subdir('src/OS')
subdir('src/Plane')
subdir('src/Polar')
subdir('src/Profile')
subdir('src/Projection')
subdir('src/Renderer')
subdir('src/Replay')
subdir('src/Repository')
subdir('src/Rough')
subdir('src/Screen')
subdir('src/Screen/Android')
subdir('src/Screen/Apple')
subdir('src/Screen/Custom')
subdir('src/Screen/EGL')
subdir('src/Screen/FB')
subdir('src/Screen/FreeType')
subdir('src/Screen/GDI')
subdir('src/Screen/GLX')
subdir('src/Screen/Memory')
subdir('src/Screen/OpenGL')
subdir('src/Screen/SDL')
subdir('src/Screen/TTY')
subdir('src/Screen/Wayland')
subdir('src/Screen/X11')
subdir('src/Task')
subdir('src/TeamCode')
subdir('src/Terrain')
subdir('src/Terrain/jasper')
subdir('src/Terrain/jasper/base')
subdir('src/Terrain/jasper/jp2')
subdir('src/Terrain/jasper/jpc')
subdir('src/Thread')
subdir('src/Time')
subdir('src/Topography')
subdir('src/Topography/shapelib')
subdir('src/Tracking')
subdir('src/Tracking/LiveTrack24')
subdir('src/Tracking/SkyLines')
subdir('src/UIUtil')
subdir('src/Units')
subdir('src/unix')
subdir('src/Util')
subdir('src/Waypoint')
subdir('src/Weather')
subdir('src/Weather/PCMet')
subdir('src/Weather/Rasp')
subdir('src/Widget')
subdir('src/XML')
subdir('src/zzip')
