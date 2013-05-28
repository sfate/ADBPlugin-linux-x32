// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

var plugin = document.getElementById('adb-plugin'),
    storageArea = chrome.storage.sync;

chrome.browserAction.setBadgeBackgroundColor({color: '#070'});

function update(oneTime) {
  if (isServerRunning()) {
    chrome.browserAction.setIcon({
      path: {
        19: 'assets/images/on_19.png',
        38: 'assets/images/on_38.png'
      }
    });
    var devices = plugin.devices().split('\n');
    devices = devices.slice(1); // Trim the header
    var count = 0;
    for (var i = 0; i < devices.length; ++i) {
      if (devices[i] !== '')
        count++;
    }
    if (count) {
      chrome.browserAction.setBadgeText({text: String(count)});
    } else {
      chrome.browserAction.setBadgeText({text: ''});
    }
    chrome.browserAction.setTitle({title: 'Stop ADB'});
  } else {
    chrome.browserAction.setIcon({
      path: {
        19: 'assets/images/off_19.png',
        38: 'assets/images/off_38.png'
      }
    });
    chrome.browserAction.setBadgeText({text: ''});
    chrome.browserAction.setTitle({title: 'Start ADB'});
  }
  if (!oneTime)
    setTimeout(update, 1000);
}

update();

function start() {
  setTimeout(function() { plugin.startServer(); });
}

function stop() {
  storageArea.remove('local-port');
  setTimeout(function() { plugin.killServer(); });
}

function isServerRunning() {
  return ('isServerRunning' in plugin) && plugin.isServerRunning();
}

function devices() {
  var port = currentPort();
  var url  = (port ? 'localhost:'+port : 'chrome://inspect');
  chrome.tabs.create({url:url});
}

function forward(port) {
  var oldPort = currentPort();
  if (port != oldPort) {
    storageArea.set({'local-port': port});
    plugin.forward(port);
  }
}

function currentPort() {
  var port;
  storageArea.get('local-port', function(result){ port = result['local-port'] });
  return port;
}

