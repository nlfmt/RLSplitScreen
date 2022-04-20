# Rocket League Split Screen Manager

This simple GUI program is very useful if you quickly want to play Rocket League\
in SplitScreen mode over two monitors.

## Requirements
1. You need to have Rocket League installed.
2. You will need exactly two monitors (if you have more, turn them off).
3. The two monitors have to have the same aspect ratio.
4. The two monitors have to be able to have the same resolution.

## Usage
- Open the program
- Click Enable

The program will adjust your monitor's resolution and edit your RL config file located\
in `Documents/My Games/Rocket League/TAGame/Config`. It will create a `.backup` file that will\
get restored when you click the disable button.

## Errors
If your setup fails to meet the aforementioned requirements, the program will fail and\
display an error message in the output window.

You may see some warnings, for example when a backup file already exists. If you overwrite\
the previous backup with a SplitScreen-modified config, you lose your initial config.\

To restore it yourself, edit `Documents/My Games/Rocket League/TAGame/Config/TASystemSettings.ini`:
- Press ctrl+f and search for ResX= & ResY=
- change the values to your display width and height

## License
This software is licensed under the MIT license.