project('utools', 'c',
        license: 'MIT',
        default_options: [
          'c_std=c11',
          'warning_level=3',
          'werror=true',
          'b_ndebug=if-release'
          ])


is_debug_build = get_option('buildtype').startswith('debug')

add_project_arguments(
  is_debug_build ? ['-DDEBUG'] : ['-DDEBUG=false'],
  #['-Weverything'],
  language: 'c',
)

is_linux = host_machine.system().startswith('linux')
is_netbsd = host_machine.system().startswith('netbsd')

if is_linux
        executable('mem', 'mem.c', 'mem_linux.c', 'util.c', install: true)
        executable('power', 'power.c', 'power_linux.c', 'util.c', install: true)
        executable('temp', 'temp.c', 'temp_linux.c', 'util.c', install: true)
endif

if is_netbsd
        cc = meson.get_compiler('c')
        lprop = cc.find_library('prop',
               dirs : ['/usr/lib/'])
        executable('mem', 'mem.c', 'mem_netbsd.c', 'util.c',  install: true)
        executable('power', 'power.c', 'power_netbsd.c', 'util.c','netbsd.c', dependencies : [lprop], install: true)
        executable('temp', 'temp.c', 'temp_netbsd.c', 'util.c','netbsd.c',dependencies : [lprop], install: true)
endif

#is_all
executable('timer', 'timer.c', install: true)
