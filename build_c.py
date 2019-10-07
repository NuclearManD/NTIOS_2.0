import os, json, sys, shutil, distutils
from distutils import dir_util

    
if_block_template = '\tif(!strcmp(cmd, "{}")){{\n\
\t\treturn {}(argv, argc);\n\
\t}}else '

ending = '{\n\
\t\tstde("Not a command:");\n\
\t\tstde(argv[0]);\n\
\t}'

set_driver_template = "\tdrivers[{}] = &{};\n"

include_template = '#include "{}"\n'

call_template = '\t{}();\n'

def list_programs(d='./build/src/programs/'):
    out = []
    for i in os.listdir(d):
        if not i.startswith('prg_'):
            continue
        i = os.path.join(d,i)
        if os.path.isdir(i):
            out.append(i)
    return out
def list_drivers(d='./build/src/drivers/'):
    out = []
    for i in os.listdir(d):
        if not i.startswith('drv_'):
            continue
        i = os.path.join(d,i)
        if os.path.isdir(i):
            out.append(i)
    return out

def setup_programs():
    with open('./build/src/programs/programs.tplt') as f:
        template = f.read()
        
    program_dirs = list_programs()

    output_ifs = ''
    include_str = ''
    inits = ''

    for i in program_dirs:
        with open(os.path.join(i, 'conf.json')) as f:
            conf = json.load(f)
        if 'disabled' in conf.keys() and conf['disabled']:
            continue # skip it
        cmd = conf['cmd']
        func = conf['entry']
        inc = os.path.basename(i)+'/'+conf['include']
        
        output_ifs+=if_block_template.format(cmd, func)
        include_str+=include_template.format(inc)

        if 'init' in conf.keys():
            inits+=call_template.format(conf['init'])
        

    output_ifs+=ending

    with open('./build/src/programs/program.c', 'w') as f:
        f.write(template.format(include_str, output_ifs, inits))

def setup_drivers():
    with open('./build/src/drivers/drivers.tplt') as f:
        template = f.read()
    driver_dirs = list_drivers()
    driver_set = ''
    preinits = ''
    inits = ''
    postinits = ''

    include_str = ''

    n_drivers = 0

    for i in driver_dirs:
        with open(os.path.join(i, 'conf.json')) as f:
            conf = json.load(f)
        if 'disabled' in conf.keys() and conf['disabled']:
            continue # skip it
        
        inc = os.path.basename(i)+'/'+conf['include']
        include_str+=include_template.format(inc)

        if 'preinit' in conf.keys():
            preinits+=call_template.format(conf['preinit'])
            
        if 'init' in conf.keys():
            inits+=call_template.format(conf['init'])
            
        if 'postinit' in conf.keys():
            postinits+=call_template.format(conf['postinit'])

        driver_set+=set_driver_template.format(n_drivers, conf['name'])
        
        n_drivers+=1
    

    with open('./build/src/drivers/drivers.c', 'w') as f:
        f.write(template.format(include_str, n_drivers, driver_set, preinits, inits, postinits))

sys.argv.append('avr')

if len(sys.argv)<2:
    print("Usage: build_c.py [platform]")
else:
    platform = sys.argv.pop()

    shutil.rmtree('./build', True)
    
    os.makedirs('./bin', exist_ok = True)
    os.makedirs('./build/src/drivers', exist_ok = True)
    os.makedirs('./build/src/programs', exist_ok = True)

    dir_util.copy_tree('./include/', './build/src/include/')
    
    dir_util.copy_tree('./programs/', './build/src/programs/')
    
    dir_util.copy_tree('./drivers/', './build/src/drivers/')
    dir_util.copy_tree('./platforms/{}/'.format(platform), './build/src/')
    
    shutil.copy('./main.cpp', './build/src/')
    shutil.copy('./NTIKernel.h', './build/src/')

    setup_programs()
    setup_drivers()

    os.chdir('./build/src/')
    os.system("sh build.sh")
    os.chdir('../..')
