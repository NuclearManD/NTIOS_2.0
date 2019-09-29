import os, json

if_block_template = '\tif(cmd=="{}"){{\n\
\t\t{}(argv, argc);\n\
\t}}else '

ending = '{\n\
\t\tstde("Not a command:");\n\
\t\tstde(argv[0]);\n\
\t}'

include_template = '#include "{}"\n'

def list_programs(d='.'):
    out = []
    for i in os.listdir(d):
        if os.path.isdir(i) and i.startswith('prg_') and len(i)>4:
            out.append(i)
    return out
with open('programs.tplt') as f:
    template = f.read()
program_dirs = list_programs()

if len(program_dirs)==0:
    print("Fatal: no programs!")
else:
    output_ifs = ''

    include_str = ''

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

    output_ifs+=ending

    with open('program.c', 'w') as f:
        f.write(template.format(include_str, output_ifs))
