import os, json

set_driver_template = "\tdrivers[{}] = &{};\n"
call_template = "\t{}();\n"

include_template = '#include "{}"\n'

def list_drivers(d='.'):
    out = []
    for i in os.listdir(d):
        if os.path.isdir(i) and i.startswith('drv_') and len(i)>4:
            out.append(i)
    return out
with open('drivers.tplt') as f:
    template = f.read()
driver_dirs = list_drivers()

if len(driver_dirs)==0:
    print("Fatal: no programs!")
else:
    driver_set = ''
    preinits = ''
    inits = ''

    include_str = ''

    n_drivers = 0

    for i in driver_dirs:
        with open(os.path.join(i, 'conf.json')) as f:
            conf = json.load(f)
        if 'disabled' in conf.keys() and conf['disabled']:
            continue # skip it
        
        inc = i+'/'+conf['include']
        include_str+=include_template.format(inc)

        if 'preinit' in conf.keys():
            preinits+=call_template.format(conf['preinit'])
            
        if 'init' in conf.keys():
            inits+=call_template.format(conf['init'])

        driver_set+=set_driver_template.format(n_drivers, conf['name'])
        
        n_drivers+=1
    

    with open('drivers.c', 'w') as f:
        f.write(template.format(include_str, n_drivers, driver_set, preinits, inits))
