import yaml
import numpy as np

def load_config(path, default_path=None):
    """
    Loads config file.

    Args:
        path (str): path to config file.
        default_path (str, optional): whether to use default path. Defaults to None.

    Returns:
        cfg (dict): config dict.

    """
    # load configuration from file itself
    with open(path, 'r') as f:
        cfg_special = yaml.full_load(f)

    # check if we should inherit from a config
    inherit_from = cfg_special.get('inherit_from')

    # if yes, load this config first as default
    # if no, use the default_path
    if inherit_from is not None:
        cfg = load_config(inherit_from, default_path)
    elif default_path is not None:
        with open(default_path, 'r') as f:
            cfg = yaml.full_load(f)
    else:
        cfg = dict()

    # include main configuration
    update_recursive(cfg, cfg_special)

    return cfg


def update_recursive(dict1, dict2):
    """
    Update two config dictionaries recursively.

    Args:
        dict1 (dict): first dictionary to be updated.
        dict2 (dict): second dictionary which entries should be used.
    """
    for k, v in dict2.items():
        if k not in dict1:
            dict1[k] = dict()
        if isinstance(v, dict):
            update_recursive(dict1[k], v)
        else:
            dict1[k] = v

class Config(object):
    '''
    Holds the configuration for anything you want it to.
    To get the currently active config, call get_cfg().

    To use, just do cfg.x instead of cfg['x'].
    I made this because doing cfg['x'] all the time is dumb.
    '''

    def __init__(self, config_dict):
        for key, val in config_dict.items():
            if isinstance(val, dict):
                self.__setattr__(key, Config(val))
            elif isinstance(val, list):
                self.__setattr__(key, np.asarray(val))
            else:
                self.__setattr__(key, val)


    def copy(self, new_config_dict={}):
        '''
        Copies this config into a new config object, making
        the changes given by new_config_dict.
        '''

        ret = Config(vars(self))

        for key, val in new_config_dict.items():
            ret.__setattr__(key, val)

        return ret

    def replace(self, new_config_dict):
        '''
        Copies new_config_dict into this config object.
        Note: new_config_dict can also be a config object.
        '''
        if isinstance(new_config_dict, Config):
            new_config_dict = vars(new_config_dict)

        for key, val in new_config_dict.items():
            self.__setattr__(key, val)
            
    def print(self):
        for k, v in vars(self).items():
            if isinstance(v, Config):
                v.print()
            else:
                print(k, ' = ', v)

# Models

def set_cfg(config_name: str):
    ''' Sets the active config. Works even if cfg is already imported! '''
    global cfg
    cfg.replace(eval(config_name))
    if cfg.name is None:
        cfg.name = config_name.split('_config')[0]
    

if __name__ == '__main__' :
    path = './default.yaml'
    cfg = load_config(path)
    
    print(cfg)
    cfg = Config(cfg)
    print(cfg.print())


