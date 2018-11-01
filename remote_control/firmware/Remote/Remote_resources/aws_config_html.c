#include "wiced_resource.h"

const char resources_apps_DIR_aws_DIR_iot_DIR_aws_config_html_data[11164] = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n" \
"<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">\r\n" \
"<html xmlns=\"http://www.w3.org/1999/xhtml\">\r\n" \
"<head>\r\n" \
"<meta http-equiv=\"Content-Type\" content=\"text/html;charset=utf-8\" />\r\n" \
"<title>Cypress WICED AWS IOT Service</title>\r\n" \
"<style type=\"text/css\">\r\n" \
".wrapper {\r\n" \
"  background: linear-gradient(45deg,rgba(125,185,232,1) 0,rgba(30,87,153,1) 100%);\r\n" \
"  position: absolute;\r\n" \
"  width: 100%;\r\n" \
"  height: 100%;\r\n" \
"  overflow: hidden;\r\n" \
"}\r\n" \
".wrapper.form-success .container h1 {\r\n" \
"  -webkit-transform: translateY(85px);\r\n" \
"      -ms-transform: translateY(85px);\r\n" \
"          transform: translateY(85px);\r\n" \
"}\r\n" \
".container {\r\n" \
"  margin: 0 auto;\r\n" \
"  text-align: center;\r\n" \
"}\r\n" \
"button, .btn {\r\n" \
"  -webkit-appearance: none;\r\n" \
"  -moz-appearance: none;\r\n" \
"  appearance: none;\r\n" \
"  outline: 0;\r\n" \
"  background-color: #16b;\r\n" \
"  text-shadow: 0 1px 1px rgba(0,0,0,0.75);\r\n" \
"  color: white;\r\n" \
"  border: 0;\r\n" \
"  padding: 10px 15px;\r\n" \
"  color: #53e3a6;\r\n" \
"  border-radius: 7px;\r\n" \
"  width: 15%;\r\n" \
"  cursor: pointer;\r\n" \
"  font-size: 14px;\r\n" \
"  -webkit-transition-duration: 0.25s;\r\n" \
"          transition-duration: 0.25s;\r\n" \
"}\r\n" \
"\r\n" \
"</style>\r\n" \
"\r\n" \
"<script type=\"text/javascript\">\r\n" \
"      var progress_run_id = null;\r\n" \
"      var control = null;\r\n" \
"      var cert_transferred = false;\r\n" \
"      var key_transferred = false;\r\n" \
"      var trigger_for_upgrade = null;\r\n" \
"      function progress( prog, current_pos, full_length, trans ) {\r\n" \
"        var node = document.getElementById(prog);\r\n" \
"        var prg_width = parseInt(document.getElementById(\'progress_plane\').style.width);\r\n" \
"        var transferring_stage = current_pos * 100 / full_length;\r\n" \
"        transferring_stage = Math.round(transferring_stage * 10) / 10;\r\n" \
"        var new_progress_bar_position = current_pos * prg_width/full_length;;\r\n" \
"        var w    = node.style.width.match(/\\\\d+/);\r\n" \
"        if (current_pos == full_length){\r\n" \
"          w = 0;\r\n" \
"          document.getElementById(trans).innerHTML=\"Transfer completed\";\r\n" \
"          node.style.width = 100 + \'%\';\r\n" \
"\r\n" \
"          if(prog == \"progress_certificate\")\r\n" \
"            cert_transferred = true;\r\n" \
"          else\r\n" \
"            key_transferred = true;\r\n" \
"\r\n" \
"          if(cert_transferred == true && key_transferred == true)\r\n" \
"          {\r\n" \
"              document.getElementById(\"reboot\").innerHTML=\"Configure WiFi to complete the procedure\";\r\n" \
"          }\r\n" \
"        }\r\n" \
"        else\r\n" \
"        {\r\n" \
"          node.style.width = new_progress_bar_position  + \'%\';\r\n" \
"          console.log(\"Updating progress\");\r\n" \
"          document.getElementById(trans).innerHTML=(\"Transferring \"+ transferring_stage.toString() + \"%\" );\r\n" \
"        }\r\n" \
"      }\r\n" \
"      function send_file_in_chunks(id){\r\n" \
"        var blobs = [];\r\n" \
"        var blob;\r\n" \
"        var xhr;\r\n" \
"        var total = 0;\r\n" \
"        var chunk_count = 0;\r\n" \
"        var image = \"certificate\";\r\n" \
"        var button = \"upload_certificate_button\";\r\n" \
"        var prog = \"progress_certificate\";\r\n" \
"        var trans = \"certificate_transfer_complete\";\r\n" \
"        if(id == 2)\r\n" \
"        {\r\n" \
"            image = \"key\";\r\n" \
"            button = \"upload_key_button\";\r\n" \
"            prog = \"progress_key\";\r\n" \
"            trans = \"key_transfer_complete\";\r\n" \
"        }\r\n" \
"        var file = document.getElementById(image).files[0];\r\n" \
"        var bytes_per_chunk = 1024;\r\n" \
"        var start = 0;\r\n" \
"        var end = bytes_per_chunk;\r\n" \
"        var size = file.size;\r\n" \
"        var upgrade_chunk_url_with_query;\r\n" \
"        var current_pos = 0;\r\n" \
"        if (window.XMLHttpRequest)\r\n" \
"        {\r\n" \
"          xhr = new XMLHttpRequest();\r\n" \
"        }\r\n" \
"        else\r\n" \
"        {\r\n" \
"          xhr = new ActiveXObject(\"Microsoft.XMLHTTP\");\r\n" \
"        }\r\n" \
"        upgrade_chunk_url_with_query = \"upgrade_chunk.html\" + \"?\" + \"file=\" + image + \"&\" + \"offset=\" + current_pos + \"&\" + \"filesize=\" + size;\r\n" \
"        xhr.open(\'POST\', upgrade_chunk_url_with_query , true);\r\n" \
"        xhr.timeout = 2000;\r\n" \
"        xhr.onreadystatechange = send_function;\r\n" \
"        function send_function()\r\n" \
"        {\r\n" \
"          if ((xhr.readyState==4 && xhr.status==200))\r\n" \
"          {\r\n" \
"            current_pos = parseInt(xhr.responseText);\r\n" \
"            console.log(\"Response received\" + current_pos);\r\n" \
"            progress(prog, current_pos, file.size, trans );\r\n" \
"            if( current_pos != file.size)\r\n" \
"            {\r\n" \
"              if (window.XMLHttpRequest)\r\n" \
"              {\r\n" \
"                xhr = new XMLHttpRequest();\r\n" \
"              }\r\n" \
"              else\r\n" \
"              {\r\n" \
"                xhr = new ActiveXObject(\"Microsoft.XMLHTTP\");\r\n" \
"              }\r\n" \
"              xhr.onreadystatechange = send_function;\r\n" \
"              upgrade_chunk_url_with_query = \"upgrade_chunk.html\" + \"?\" + \"file=\" + image + \"&\" + \"offset=\" + current_pos + \"&\" + \"filesize=\" + file.size;\r\n" \
"              xhr.open(\'POST\', upgrade_chunk_url_with_query, true);\r\n" \
"              xhr.timeout = 4000;\r\n" \
"              chunk_count++;\r\n" \
"              console.log(\"Sending\" + chunk_count);\r\n" \
"              xhr.send(file.slice(current_pos, ( current_pos + 1024 )));\r\n" \
"            }\r\n" \
"          }\r\n" \
"          else\r\n" \
"          {\r\n" \
"            if ( (xhr.readyState==4 && xhr.status==0) )\r\n" \
"            {\r\n" \
"              if (window.XMLHttpRequest)\r\n" \
"              {\r\n" \
"                xhr = new XMLHttpRequest();\r\n" \
"              }\r\n" \
"              else\r\n" \
"              {\r\n" \
"                xhr = new ActiveXObject(\"Microsoft.XMLHTTP\");\r\n" \
"              }\r\n" \
"              xhr.onreadystatechange = send_function;\r\n" \
"              upgrade_chunk_url_with_query = \"upgrade_chunk.html\" + \"?\" + \"file=\" + image + \"&\" + \"offset=\" + current_pos + \"&\" + \"filesize=\" + file.size;\r\n" \
"              xhr.open(\'POST\', upgrade_chunk_url_with_query, true);\r\n" \
"              xhr.timeout = 4000;\r\n" \
"              console.log(\"Resending after comms failure\" + chunk_count + total );\r\n" \
"              xhr.send(file.slice(current_pos, ( current_pos + 1024 )));\r\n" \
"            }\r\n" \
"            else\r\n" \
"            {\r\n" \
"              console.log(\"Status =\" + xhr.readyState + \"  \" + xhr.status );\r\n" \
"            }\r\n" \
"          }\r\n" \
"        }\r\n" \
"        xhr.send(file.slice(0, 1024));\r\n" \
"      }\r\n" \
"      trigger_for_upgrade = document.getElementById(\"upgrade_certificate_button\");\r\n" \
"      control = document.getElementById(\"certificate\");\r\n" \
"      console.log(\"Here 2\");\r\n" \
"</script>\r\n" \
"<script>\r\n" \
"        function update_settings(){\r\n" \
"            var thing, url, msg;\r\n" \
"            thing = document.getElementById(\'thing\').value;\r\n" \
"            msg = document.getElementById(\"save_message\");\r\n" \
"            url = \"configuration_settings.html?mode=set\" + \"&thing=\" + thing;\r\n" \
"            var xhttp = new XMLHttpRequest();\r\n" \
"              xhttp.onreadystatechange = function() {\r\n" \
"                if (xhttp.readyState == 4 && xhttp.status == 200) {\r\n" \
"                  msg.innerHTML = \"Settings saved successfully\";\r\n" \
"                  setTimeout(function(){\r\n" \
"                    msg.innerHTML = \"\";\r\n" \
"                  },5000);\r\n" \
"                }\r\n" \
"              }\r\n" \
"              xhttp.open(\"POST\", url, true);\r\n" \
"              xhttp.send();\r\n" \
"        }\r\n" \
"\r\n" \
"        function get_settings(){\r\n" \
"            var url = \"configuration_settings.html?mode=get\";\r\n" \
"            var xhttp = new XMLHttpRequest();\r\n" \
"            xhttp.onreadystatechange = function() {\r\n" \
"                if (xhttp.readyState == 4 && xhttp.status == 200) {\r\n" \
"                  document.getElementById(\'thing\').value = xhttp.responseText;\r\n" \
"                  setTimeout(function(){\r\n" \
"                    msg.innerHTML = \"\";\r\n" \
"                  },5000);\r\n" \
"                }\r\n" \
"              }\r\n" \
"              xhttp.open(\"POST\", url, true);\r\n" \
"              xhttp.send();\r\n" \
"        }\r\n" \
"\r\n" \
"</script>\r\n" \
"</head>\r\n" \
"\r\n" \
"<div width=\"98%\">\r\n" \
"<table border=\'0\' cellpadding=\'0\' cellspacing=\'0\' width=\"98%\">\r\n" \
" <tr style=\"border-collapse: collapse; padding: 0;\">\r\n" \
"   <td style=\"width:20px\"></td>\r\n" \
"   <td style=\"width:152px\"><img src=\"../../images/cypresslogo.png\" alt=\"Cypress Logo\" /></td>\r\n" \
"   <td style=\"vertical-align:middle; text-align:center; font: bold 25px/100% Verdana, Arial, Helvetica, sans-serif;background-image:url(\'../../images/cypresslogo_line.png\');\">\r\n" \
"   WICED&trade; AWS IOT Service\r\n" \
"   </td>\r\n" \
"   <td style=\"width:137px;background-image:url(\'../../images/cypresslogo_line.png\');\"></td>\r\n" \
" </tr>\r\n" \
" <tr><td>&nbsp;&nbsp;&nbsp;</td></tr>\r\n" \
"</table>\r\n" \
"\r\n" \
"</div>\r\n" \
"<div class=\"wrapper\">\r\n" \
"<div class=\"container\">\r\n" \
"   <body onload=\"get_settings()\">\r\n" \
"   <div id=\"settings\" class=\"settings\">\r\n" \
"   <fieldset align =\"center\" style = \"border: 1px solid rgb(255,232,57);width: 60%;margin:auto;margin-top:3%; border-radius: 5px;padding: 15px;\">\r\n" \
"      <legend style=\"font: bold 15px/100% Verdana, Arial, Helvetica, sans-serif;\">Configuration Settings : </legend>\r\n" \
"        <label for=\"thing\" style=\"padding-right:1%;font: bold 15px/100% Verdana, Arial, Helvetica, sans-serif;\">Thing Name</label>\r\n" \
"        <input id=\"thing\" type=\"text\" style=\"margin-right:8%\" placeholder=\"thing-name\" />\r\n" \
"        <br/>\r\n" \
"        <br/>\r\n" \
"        <Button id=\"save_settings\" class=\"save_settings\" onclick=\"update_settings()\">Save Settings</Button>\r\n" \
"        <p id=\"save_message\"></p>\r\n" \
"        </fieldset>\r\n" \
"        </div>\r\n" \
"      <br/>\r\n" \
"      <br/>\r\n" \
"\r\n" \
"    <fieldset align =\"center\" style = \"border: 1px solid rgb(255,232,57);width: 60%;margin:auto;\">\r\n" \
"    <legend style=\"font: bold 15px/100% Verdana, Arial, Helvetica, sans-serif;\"> Upload Certificate and Key :</legend>\r\n" \
"    <div class=\"upload_certificate\" style=\"padding-top:35px\">\r\n" \
"      <input class=\"file_selector\" type=\"file\" name=\"Select certificate\" id=\"certificate\"></input>\r\n" \
"      <button class= \"upload_certificate_button\" type=\"button\" id=\"upgrade_certificate_button\" onclick=\"send_file_in_chunks(1)\" >Upload Certificate</button>\r\n" \
"      <div id=\"progress_plane\" style=\" background-color:rgba(165, 167, 169, 0.39); border-radius: 10px; margin-left:27%; margin-top:2%; border: 1px solid rgba(0, 58, 255, 0.93); width:45%; height:15px; font-family: arial, arial, arial; top:10; left:10; position:relative;\"/>\r\n" \
"      <div id=\"progress_certificate\" style=\" border-radius: 10px; height:100%; width:0px; background-color:#0065E9; top:10; left:10;\"></div>\r\n" \
"      <h5 class=\"one\" id = \"certificate_transfer_complete\"></h5>\r\n" \
"      </div>\r\n" \
"      <br/>\r\n" \
"      <br/>\r\n" \
"\r\n" \
"      <div class=\"upload_key\">\r\n" \
"      <input class=\"file_selector\" type=\"file\" name=\"Select key\" id=\"key\"></input>\r\n" \
"      <button class= \"upload_key_button\" type=\"button\" id=\"upload_key_button\" onclick=\"send_file_in_chunks(2)\" >Upload key</button>\r\n" \
"      <div id=\"progress_plane\" style=\" background-color:rgba(165, 167, 169, 0.39); border-radius: 10px;margin-left:27%; margin-top:2%; border: 1px solid rgba(0, 58, 255, 0.93); width:45%; height:15px; font-family: arial, arial, arial; top:10; left:10; position:relative;\"/>\r\n" \
"      <div id=\"progress_key\" style=\" border-radius: 10px; height:100%; width:0px; background-color:#0065E9; top:10; left:10;\"></div>\r\n" \
"      <h5 class=\"one\" id = \"key_transfer_complete\"></h5>\r\n" \
"      </div>\r\n" \
"\r\n" \
"      <br/>\r\n" \
"      <br/>\r\n" \
"      <br/>\r\n" \
"      <h4 class=\"one\" id = \"reboot\"></h4>\r\n" \
"      <input type=\"button\" class =\"btn\" value=\"Wi-Fi Setup >\" onclick=\"document.location.href=\'scan_page_outer.html\'\" />\r\n" \
"      <br/>\r\n" \
"      <br/>\r\n" \
"      </frameset>\r\n" \
"      </body>\r\n" \
"\r\n" \
"      </div>\r\n" \
"      </div>\r\n" \
"</html>\r\n" \
"";
const resource_hnd_t resources_apps_DIR_aws_DIR_iot_DIR_aws_config_html = { RESOURCE_IN_MEMORY, 11163, { .mem = { resources_apps_DIR_aws_DIR_iot_DIR_aws_config_html_data }}};
