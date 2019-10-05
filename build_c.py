import os, json, sys, shutil

    
if_block_template = '\tif(!strcmp(cmd, "{}")){{\n\
\t\treturn {}(argv, argc);\n\
\t}}else '

ending = '{\n\
\t\tstde("Not a command:");\n\
\t\tstde(argv[0]);\n\
\t}'

include_template = '#include "{}"\n'

init_template = '\t{}();\n'

def list_programs(d='./build/src/programs'):
    out = []
    for i in os.listdir(d):
        if os.path.isdir(i) and i.startswith('prg_') and len(i)>4:
            out.append(i)
    return out

if len(sys.argv)<2:
    print("Usage: build_c.py [platform]")
else:
    platform = sys.argv.pop()
    
    os.makedirs('./build/src/drivers', exist_ok = True)
    os.makedirs('./build/src/programs', exist_ok = True)
    shutil.copy('./drivers/*', './build/src/drivers/')
    shutil.copy('./platforms/{}/drivers/*'.format(platform), './build/src/drivers/')
    shutil.copy('./main.cpp', './build/src/')
    shutil.copy('./NTIKernel.h', './build/src/')
    with open('programs.tplt') as f:
        template = f.read()
    program_dirs = list_programs()

    if len(program_dirs)==0:
        print("Fatal: no programs!")
    else:
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
            inc = i+'/'+conf['include']
            
            output_ifs+=if_block_template.format(cmd, func)
            include_str+=include_template.format(inc)

            if 'init' in conf.keys():
                inits+=init_template.format(conf['init'])
            

        output_ifs+=ending

        with open('program.c', 'w') as f:
            f.write(template.format(include_str, output_ifs, inits))
