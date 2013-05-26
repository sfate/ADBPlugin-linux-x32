# ADB Plugin

ADB Plugin is a Chrome Extension that runs ADB daemon and enables remote debugging for mobile.

## How to run on Linux(x32)
- Visit https://github.com/Sfate/ADBPlugin-linux-x32/raw/master/npADBPlugin-lastest.crx and download extension.
- Go to `chrome://extensions` and drop that file there.
- Click little Android icon next to address bar.

## How to build on Linux(x32)
- Get FireBreath at http://www.firebreath.org/display/documentation/Download
- Run `$FIREBREATH_FULL_PATH/prepmake.sh $PROJECT_ROOT_DIR/chrome-extension/plugin/src/ADBPlugin`
- Then compile it into a lib: `cd $FIREBREATH_FULL_PATH/build/projects/ADBPlugin/ && make`
- Copy lib into extentions folder: `cp $FIREBREATH_FULL_PATH/build/bin/ADBPlugin/npADBPlugin.so $PROJECT_ROOT_DIR/chrome-extension/plugin/npADBPlugin.so`
- Navigate to `$PROJECT_ROOT_DIR` and run `chmod +x build.sh && ./build.sh`
- Complete extention will be available at the project root directory by name `npADBPlugin-linux-x32.crx`

## Architecture
- Need to be tested on x64 and non-debian based systems.

## License

This is a port of https://github.com/repenaxa/ADBPlugin for Linux.

And i beelive that this should be under the MIT License.
Please inform me if it's not. =)

