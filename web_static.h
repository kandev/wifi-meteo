const char PAGE_favicon[] PROGMEM = R"=====(
<svg version="1.0" id="Layer_1" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" x="0px" y="0px"
   viewBox="0 0 150 150" enable-background="new 0 0 150 150" xml:space="preserve">
<g>
  <path fill="#000000" d="M74.8,48.3c-8.6,6.2-17.5,12-26.1,18.2l-0.2,0C42.1,71,21.3,85.5,8,94.6l7.5,1.2c18.8-13,44.8-31,56.6-39.3
    c1.2-0.7,2.7-2.5,4.1-1c11.5,8,23.1,16,34.7,24c7.6,5.2,15.2,10.5,22.8,15.7l7.1-1.1l-33.6-23.7C96.3,63.2,85.7,55.6,74.8,48.3z"/>
  <path fill="#000000" d="M40.3,64.2c11.5-8,23.1-16.1,34.7-24c11.8,8.2,23.7,16.4,35.5,24.6l16.9-29.4l-39.3,12L73,9.3L57.9,47.5
    l-39.3-12l18,31.3c1.5-1,2.7-1.8,3.5-2.3L40.3,64.2z"/>
  <path fill="#000000" d="M75,62.7c-10.6,7.1-32.1,22.2-49.9,34.6l20.8,3.2l-3,41L73,113.5l30.2,27.9l-3-41l23.9-3.6
    c-6-4.2-12-8.4-18-12.5C95.8,77,85.3,70,75,62.7z M73.4,109.6c-4.1,0.1-8.1,0.1-12.2,0.1c0-4.1,0-8.1,0.1-12.2c4,0,8.1,0,12.1,0
    C73.4,101.6,73.4,105.6,73.4,109.6z M61.2,94.4c0-4,0-8,0-12.1c4.1,0,8.1,0,12.2,0c0,4,0,8,0,12.1C69.3,94.4,65.3,94.4,61.2,94.4z
     M88.7,82.3c0,4,0,8.1,0,12.1c-4,0-8.1,0-12.1,0c0-4.1,0-8.1,0-12.1C80.6,82.3,84.7,82.3,88.7,82.3z M76.6,109.7
    c0-4,0-8.1,0.1-12.1c4,0,8,0,12.1,0c0,4,0,8,0.1,12.1C84.7,109.8,80.6,109.8,76.6,109.7z"/>
</g>
</svg>
)=====";

const char PAGE_root[] PROGMEM = R"=====(
  <!DOCTYPE HTML><html>
  <head>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="icon" href="/favicon.svg" type="image/svg+xml">
    <title></title>
<style>
body {
  background-color: #000;
  color: #ccc;
  font-family: Arial;
  font-size: 14px;
  padding: 0px;
  margin: 0px;
}

h3 {
  background-color: #444444;
  color: #ffa600;
  margin: 0px;
  padding: 8px;
} 
input[type=text] {
  background-color: #000;
  border: 1px solid #ffa600;
  border-radius: 4px;
  color: #fff;
  margin:2px;
  width: 150px;
}
select {
  background-color: #000;
  border: 1px solid #ffa600;
  border-radius: 4px;
  color: #fff;
  margin:0;
  margin-left:2px;
  width: 156px;
}
textarea {
  background-color: #000;
  border: 1px solid #ffa600;
  border-radius: 4px;
  color: #fff;
  margin:0;
  margin-left:2px;
  width: 156px;
}
input[type=submit] {
  background-color: #ffa600;
  border: 1px solid #000;
  border-radius: 4px;
  padding: 5px;
  padding-left: 30px;
  padding-right: 30px;
  font-weight: bold;
}
label {
  font-size: 0.8em;
}
fieldset{
  border: solid 1px #00c8ff;  
  float:left;
  font-size: 0.9em;
  margin:2px;
}
fieldset legend {
  color: #fff;
}
.cc {
  color: #ffa600;
  font-size: 0.75em;
  text-decoration: none;
}
.cc:hover {
  color: #ffa600;
  text-decoration: underline;
}
.data {
  color: #ffd500;
  font-weight: bold;
}
.gpio_off {
  color: #aaa;
  background-color: #000;
  border: 1px solid #aaa;
  border-radius: 4px;
  padding: 4px;
  padding-left: 20px;
  padding-right: 20px;
  font-weight: bold;
  margin: 5px;
}
.gpio_on {
  color: #000;
  background-color: #aaa;
  border: 1px solid #000;
  border-radius: 4px;
  padding: 4px;
  padding-left: 20px;
  padding-right: 20px;
  font-weight: bold;
  margin: 5px;
}
.gpio_on:hover {
  border: 1px solid #fff;
}
.gpio_off:hover {
  border: 1px solid #fff;
}
.small_button {
  color: #aaa;
  background-color: #000;
  border: 1px solid #ffa600;
  border-radius: 3px;
  padding:1px;
  padding-left:4px;
  padding-right:4px;
  margin:1px;
}
.small_button:hover {
  color: #fff;
}
.sched {
  background-color: #000;
  border: 1px solid #ffa600;
  border-radius: 4px;
  color: #fff;
  margin: 2px;
  width:40px;
}
</style>

  </head><body>
  <h3>Configuration menu</h3>
  <div style="margin:10px; width: *; overflow:hidden;"><form action="/configure" method="post">
  <fieldset style="height:180px;">
  <legend>General</legend>
    <label for="hostname">Hostname:</label><br>
    <input type="text" name="hostname" id="hostname" value=""><br>
    <label for="dmin_password">Admin password:</label><br>
    <input type="text" name="admin_password" id="admin_password" value=""><br>
  </fieldset>
  <fieldset style="height:180px;">
  <legend>Wifi network</legend>
    <label for="ssid">SSID:</label><br>
    <input type="text" name="ssid" id="ssid" value="" style="width:110px;"><input type="button" id="scan" value="Scan" onclick="wifi_scan();" class="small_button"><br>
    <select id="wifis" size="4" onchange="document.getElementById('ssid').value=this.value;">
    </select><br>
    <label for="password">Password:</label><br>
    <input type="text" name="password" id="password" value="">
  </fieldset>

  <fieldset style="border: solid 1px #11ff00; height:180px;">
    <legend>Status</legend>
    Version: <span class="data" id="version"></span><br>
    MAC: <span class="data" id="mac"></span><br>
    RSSI: <span class="data" id="rssi"></span><span class="data"></span><br>
    Vcc: <span class="data" id="vcc"></span><span class="data"></span><br>
    Flash chip size: <span class="data" id="flash_size"></span><br>
    Temperature: <span class="data" id="temperature"></span><br>
    Humidity: <span class="data" id="humidity"></span><br>
  </fieldset>
  </div>
  <div style="text-align:center;padding:15px;">
  <input type="submit" value=" SAVE ">
  </div>
  </form>
  <div style="padding:2px;">
  <fieldset style="border: solid 1px #ff0000;">
  <legend>Important</legend>
  Please verify all the data before you click SAVE as there is no error correction. If you enter wrong data and the device disappears from your sight - hold GPIO0 to ground for 10 seconds (this will do factory reset).
  </fieldset>
</div>
  <script type="text/javascript">
  function updateData() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        var data = JSON.parse(this.responseText);
        if (data.hostname!="") document.getElementById("hostname").value = data.hostname;
        if (data.admin_password!="") document.getElementById("admin_password").value = data.admin_password;
        if (data.ssid!="") document.getElementById("ssid").value = data.ssid;
        if (data.password!="") document.getElementById("password").value = data.password;

        if (data.version!="") document.getElementById("version").textContent = data.version;
        if (data.mac!="") document.getElementById("mac").textContent = data.mac;
        if (data.rssi!="") document.getElementById("rssi").textContent = data.rssi + 'dBi';
        if (data.vc!="") document.getElementById("vcc").textContent = data.vcc + 'V';
        if (data.flash_size!="") document.getElementById("flash_size").textContent = data.flash_size;
        if (data.hostname!="") document.getElementById("h1").textContent = data.hostname;
        if (data.hostname!="") document.getElementById("h2").textContent = data.hostname;
        if (data.hostname!="") document.getElementById("h3").textContent = data.hostname;
        if (data.hostname!="") document.title = data.hostname;
        if (data.t!="") document.getElementById("temperature").textContent = data.t + String.fromCharCode(176) + 'C';
        if (data.h!="") document.getElementById("humidity").textContent = data.h + '%';
        var opts='';
        var array=[];
        for(var w in data.wifis){
          array.push({ssid:w,rssi:data.wifis[w]})
        }
        array.sort(function(a,b){return a.rssi - b.rssi});
        array.reverse();
        for(var i in array) {
          var col='#ff0000';
          if (array[i].rssi>-90) col='#ffaa00';
          if (array[i].rssi>-80) col='#ffff00';
          if (array[i].rssi>-65) col='#00ff00';
          opts+='<option value="' + array[i].ssid + '" style="color: ' + col + ';" ';
          if (array[i].ssid==data.ssid) opts+=' selected';
          opts+='>' + array[i].ssid + ' [' + array[i].rssi + '] ';
          if (array[i].ssid==data.ssid) opts+='<-';
          opts+='</option>';
        }
        document.getElementById("wifis").innerHTML=opts;
      }
    };
    xhttp.open("GET", "/data", true);
    xhttp.send();
  }
  function updateDynamicData() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        var data = JSON.parse(this.responseText);
        if (data.rssi!="") document.getElementById("rssi").textContent = data.rssi;
        if (data.vc!="") document.getElementById("vcc").textContent = data.vcc;
        if (data.t!="") document.getElementById("temperature").textContent = data.t + String.fromCharCode(176) + 'C';
        if (data.h!="") document.getElementById("humidity").textContent = data.h + '%';
      }
    };
    xhttp.open("GET", "/data", true);
    xhttp.send();
  }
  
  function wifi_scan() {
    document.getElementById("scan").style.backgroundColor="#444";
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        var data = JSON.parse(this.responseText);
        if (data.ssid!="") document.getElementById("ssid").value = data.ssid;
        var opts='';
        var array=[];
        for(var w in data.wifis){
          array.push({ssid:w,rssi:data.wifis[w]})
        }
        array.sort(function(a,b){return a.rssi - b.rssi});
        array.reverse();
        for(var i in array) {
          var col='#ff0000';
          if (array[i].rssi>-90) col='#ffaa00';
          if (array[i].rssi>-85) col='#ffff00';
          if (array[i].rssi>-65) col='#00ff00';
          opts+='<option value="' + array[i].ssid + '" style="color: ' + col + ';" ';
          opts+='>' + array[i].ssid + ' [' + array[i].rssi + '] ';
          if (array[i].ssid==data.ssid) opts+='<-';
          opts+='</option>';
        }
        document.getElementById("wifis").innerHTML=opts;
        document.getElementById("scan").style.backgroundColor="";
      }
    };
    xhttp.open("GET", "/scan", true);
    xhttp.send();
  }
  updateData();
  wifi_scan();
  window.setInterval(updateDynamicData,10000);
  
  </script>
<div style="position: fixed; bottom: 0; width: 100%; text-align: right;">
&copy; <a class="cc" href="http://kandev.com" title="kandev.com" target="_blank">kandev.com</a>
</div>
  </body></html>
  )=====";

void get_data() {
  if ((!server.authenticate("admin", _ADMIN_PASS.c_str())) && (_CLIENT))
    server.requestAuthentication();
  server.send ( 200, F("application/json"), "{ \"hostname\":\"" + String(_HOSTNAME) + "\", \
        \"ssid\":\"" + String(_SSID) + "\", \
        \"password\":\"" + String(_PASS) + "\", \
        \"admin_password\":\"" + _ADMIN_PASS + "\", \
        \"version\":\"" + String(_VERSION) + "\", \
        \"rssi\":\"" + String(WiFi.RSSI()) + "\", \
        \"flash_size\":\"" + ESP.getFlashChipRealSize() / 1024 + "KB\", \
        \"mac\":\"" + getMacAddress() + "\", \
        \"vcc\":\"" + String(float(ESP.getVcc() / 1000.0)) + "\", \
        \"t\":\"" + t + "\", \
        \"h\":\"" + h + "\" \
                }" );
}

bool loadConfig() {
  _HOSTNAME = String(_PRODUCT) + "-" + getMacAddress().substring(6);
  _HOSTNAME.toLowerCase();
  openFS();
  File configFile = SPIFFS.open(_CONFIG, "r");
  if (!configFile) {
    Serial.println(F("[ERR] No configuration found."));
    return false;
  }

  size_t size = configFile.size();
  if (size > 1024) {
    Serial.println(F("[ERR] configuration file is too large."));
    return false;
  }

  std::unique_ptr<char[]> buf(new char[size]);
  configFile.readBytes(buf.get(), size);
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& json = jsonBuffer.parseObject(buf.get());

  if (!json.success()) {
    Serial.println(F("[ERR] Can't parse configuration file."));
    return false;
  }
  const char* ssid = json["ssid"];
  const char* pass = json["pass"];
  const char* hostname = json["hostname"];
  const char* admin_pass = json["admin_password"];

  if (String(hostname) != "")
    _HOSTNAME = hostname;
  _SSID = ssid;
  _PASS = pass;
  _ADMIN_PASS = admin_pass;

  if (_ADMIN_PASS.length() == 0) _ADMIN_PASS = "";
  if (_SSID.length() == 0) _SSID = "";
  if (_PASS.length() == 0) _PASS = "";

  Serial.print(F("SSID: "));
  Serial.println(_SSID);
  closeFS();
  return true;
}

void handle_configure() {
  if ((!server.authenticate("admin", _ADMIN_PASS.c_str())) && (_CLIENT))
    server.requestAuthentication();
  bool newssid, newpass;
  for (int i = 0; i < server.args(); i++) {
    if (server.argName(i) == "ssid") {
      (_SSID == server.arg(i)) ? (newssid = false) : (newssid = true);
      _SSID = server.arg(i);
    }
    if (server.argName(i) == "password") {
      (_PASS == server.arg(i)) ? (newpass = false) : (newpass = true);
      _PASS = server.arg(i);
    }
    if (server.argName(i) == "hostname") _HOSTNAME = server.arg(i);
    if (server.argName(i) == "admin_password") _ADMIN_PASS = server.arg(i);
  }
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();
  json["ssid"] = _SSID;
  json["pass"] = _PASS;
  json["hostname"] = _HOSTNAME;
  json["admin_password"] = _ADMIN_PASS;

  openFS();
  File configFile = SPIFFS.open(_CONFIG, "w");
  int error = 0;
  if (!configFile) {
    Serial.println(F("[ERR] Configuration can't be saved for some reason."));
    error = 1;
  }
  json.printTo(configFile);
  closeFS();
  if (error == 0) {
    server.send(200, F("text/html"), F("<meta http-equiv=\"refresh\" content=\"5; url=/\" />[OK]"));
  } else {
    server.send(200, F("text/plain"), F("[ERR]"));
  }
  if ((newssid) && (newpass)) ESP.restart();
}

void handle_showconfig() {
  if (!server.authenticate("admin", _ADMIN_PASS.c_str()))
    server.requestAuthentication();
  openFS();
  if (SPIFFS.exists(_CONFIG)) {
    File file = SPIFFS.open(_CONFIG, "r");
    size_t sent = server.streamFile(file, F("text/plain"));
    file.close();
  } else {
    server.send(200, F("text/plain"), F("Config file not found."));
  }
  closeFS();
}

