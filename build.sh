#!/bin/bash

set -e

FIREBREATH_FULL_PATH=$1
PROJECT_ROOT_DIR="$PWD"

$FIREBREATH_FULL_PATH/prepmake.sh $PROJECT_ROOT_DIR/plugin-src/ADBPlugin
cd $FIREBREATH_FULL_PATH/build/projects/ADBPlugin/ && make
cp $FIREBREATH_FULL_PATH/build/bin/ADBPlugin/npADBPlugin.so $PROJECT_ROOT_DIR/chrome-extension/plugin/npADBPlugin.so

EXT_DIR="$PROJECT_ROOT_DIR/chrome-extension"
EXT_PEM="$EXT_DIR.pem"

name="npADBPlugin-linux-x32"
crx="$PROJECT_ROOT_DIR/$name.crx"
pub="$PROJECT_ROOT_DIR/$name.pub"
sig="$PROJECT_ROOT_DIR/$name.sig"
zip="$PROJECT_ROOT_DIR/$name.zip"
trap 'rm -f "$pub" "$sig" "$zip"' EXIT

(cd "$EXT_DIR" && zip -qr -9 -X "$zip" .)

cd $PRJ_DIR && openssl genrsa -out "$EXT_PEM" 1024
openssl sha1 -sha1 -binary -sign "$EXT_PEM" < "$zip" > "$sig"
openssl rsa -pubout -outform DER < "$EXT_PEM" > "$pub" 2>/dev/null

byte_swap () {
  # Take "abcdefgh" and return it as "ghefcdab"
  echo "${1:6:2}${1:4:2}${1:2:2}${1:0:2}"
}

crmagic_hex="4372 3234" # Cr24
version_hex="0200 0000" # 2
pub_len_hex=$(byte_swap $(printf '%08x\n' $(ls -l "$pub" | awk '{print $5}')))
sig_len_hex=$(byte_swap $(printf '%08x\n' $(ls -l "$sig" | awk '{print $5}')))
(
  echo "$crmagic_hex $version_hex $pub_len_hex $sig_len_hex" | xxd -r -p
  cat "$pub" "$sig" "$zip"
) > "$crx"
echo "Wrote $crx"
rm $EXT_PEM

exit 0
