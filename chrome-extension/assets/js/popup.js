var start = document.getElementById('start'),
    stop  = document.getElementById('stop'),
   plugin = chrome.extension.getBackgroundPage(),
  devices = document.getElementById('devices');

if (plugin.isServerRunning()) {
  start.classList.add('disabled');
} else {
  devices.classList.add('disabled');
  stop.classList.add('disabled');
}

devices.addEventListener('click', function () {
  if (devices.classList.contains('disabled'))
    return;
  plugin.devices();
  window.close();
}, false);

start.addEventListener('click', function () {
  if (start.classList.contains('disabled'))
    return;
  plugin.start();
  window.close();
}, false);

stop.addEventListener('click', function () {
  if (stop.classList.contains('disabled'))
    return;
  plugin.stop();
  window.close();
}, false);
