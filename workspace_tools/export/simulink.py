"""
mbed SDK
Copyright (c) 2011-2013 ARM Limited

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
"""
from exporters import Exporter
from os.path import splitext, basename


class SIMULINK(Exporter):
    NAME = 'SIMULINK'
    TOOLCHAIN = 'GCC_ARM'

    TARGETS = [
        'ARCH_MAX',
#        'DISCO_F051R8',
#        'DISCO_F100RB',
#        'DISCO_F303VC',
#        'DISCO_F334C8',
#        'DISCO_F401VC',
        'DISCO_F407VG',
        'DISCO_F429ZI',
        'DISCO_F746NG',
#        'DISCO_L053C8',
        'NUCLEO_F401RE',
        'NUCLEO_F411RE',
        'NUCLEO_F446RE',
#        'NUCLEO_F030R8',
        'NUCLEO_F042K6',
#        'NUCLEO_F070RB',
#        'NUCLEO_F072RB',
#        'NUCLEO_F091RC',
#        'NUCLEO_F103RB',
#        'NUCLEO_F302R8',
        'NUCLEO_F303RE',
        'NUCLEO_F303K8',
#        'NUCLEO_F334R8',
#        'NUCLEO_L053R8',
#        'NUCLEO_L073RZ',
#        'NUCLEO_L152RE',
    ]

    DOT_IN_RELATIVE_PATH = True

    def generate(self):
        # "make" wants Unix paths
        self.resources.win_to_unix()

        to_be_compiled = []
        object_files   = []
        for r_type in ['s_sources', 'c_sources', 'cpp_sources']:
            r = getattr(self.resources, r_type)
            if r:
                for source in r:
                    if not source == "./main.cpp" and not source.startswith("./env/"):
                        to_be_compiled.append(source)
                        base, ext = splitext(source)
                        object_files.append(base + '.o')

        libraries = []
        for lib in self.resources.libraries:
            l, _ = splitext(basename(lib))
            libraries.append(l[3:])

        ctx = {
            'name': self.program_name,
            'to_be_compiled': to_be_compiled,
            'object_files': object_files,
            'include_paths': self.resources.inc_dirs,
            'library_paths': self.resources.lib_dirs,
            'linker_script': self.resources.linker_script,
            'libraries': libraries,
            'symbols': self.get_symbols()
        }
        self.gen_file('simulink_%s.tmpl' % self.target.lower(), ctx, 'target_tools.mk')
