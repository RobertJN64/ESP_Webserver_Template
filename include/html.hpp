#include <Arduino.h>
#ifndef HTML_H
#define HTML_H

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ESP Webserver Demo</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <script>
    var changed = false;
    
    function get_request(url) {
      var xhr = new XMLHttpRequest();
      xhr.open("GET", url);
      xhr.send();
    }

    function get_request_async(url, done) {
      var request = new XMLHttpRequest();
      request.open("GET", url);

      request.onload = function () {
          done(request.responseText)
      }
      request.onerror = function () {}
      request.send();
    }

    function add_table_row(name, option, text) {
      var tbody = document.getElementById('json_table').children[1];
      var tr = document.createElement('tr');
      tr.id = name;
      tr.innerHTML += `<td>${name}</td>`
      tr.innerHTML += `<td>
        <select id="option_${name}" onchange="change()">
            <option value="A">Group A</option>
            <option value="B">Group B</option>
            <option value="C">Group C</option>
        </select></td>`
      tr.innerHTML += `<td><input id="text_${name}" type="text" value="${text}" onchange="change()"></td>`
      tr.innerHTML += `<td><button class="nice_button" style="background-color: red" onclick="delete_row('${name}')">Delete Row</button></td>`
      tbody.appendChild(tr);
      document.getElementById("option_" + name).value = option;
    }

    function load_json(data) {
        data = JSON.parse(data);
        for (var key of Object.keys(data)) {
            add_table_row(key, data[key]['option'], data[key]['text']);
        }
    }

    function change() {
        document.getElementById("savebtn").disabled = false;
        document.getElementById("savebtn").style.backgroundColor = "green";
        changed = true;
    }

    function second_page() {
        if (changed) {
            if (!confirm("Table has unsaved changes, leaving the page will delete those changes.")) {
                return;
            }
        }
        location.href = '/second_page';
    }

    function add_row() {
        var name = prompt("Sequence name?");
        var tbody = document.getElementById('json_table').children[1];
        for (var i = 0; i < tbody.children.length; i++) {
            if (tbody.children[i].id == name) {
                alert("Name taken!");
                return;
            };
        }
        if (name != "") {
            add_table_row(name, "A", "");
            change();
        }
    }

    function get_table_json(validate) {
      var tbody = document.getElementById('json_table').children[1];
      var returnjson = {};
      for (var i = 0; i < tbody.children.length; i++) {
        var new_item = {};
        var id = tbody.children[i].id;
        new_item['option'] = document.getElementById("option_" + id).value;
        new_item['text'] = document.getElementById("text_" + id).value;

        if (validate) {
            if (new_item['text'] == "") {
                alert("Text field empty!");
                return false;
            }
        }
        returnjson[id] = new_item;
      }
      return returnjson;
    }

    function save() {
      returnjson = get_table_json(true);
      if (returnjson) {
        document.getElementById("savebtn").disabled = true;
        document.getElementById("savebtn").style.backgroundColor = "darkgrey";
        var request = new XMLHttpRequest();
        request.open("POST", "/set_json");
        request.setRequestHeader("Content-Type", "application/json")
        request.send(JSON.stringify(returnjson));
        changed = false;
      }
    }

    function delete_row(name) {
        if (confirm("Are you sure you want to delete this row?")) {
            document.getElementById("json_table").children[1].removeChild(document.getElementById(name));
            save();
        }
    }
  </script>
  <link rel="stylesheet" href="/stylesheet">
</head>
<body>
    <h2 style="text-align: center">~HEADER~</h2>
    <div class="roundedDiv">
      <table id="json_table">
          <thead>
              <tr>
                <th>Name</th>
                <th>Option</th>
                <th>Text Input</th>
                <th>Delete</th>
              </tr>
          </thead>
          <tbody>
          </tbody>
      </table>
      <button onclick="add_row()" class="nice_button" style="background-color: blue">Add row!</button>
      <button disabled id="savebtn" onclick="save()" class="nice_button" style="background-color: darkgrey">Save updates!</button>
    </div>
    <button onclick="second_page()" style="background-color: blue" class="nice_button">Go to second page!</button>
    <button onclick="get_request('/blink_led')" style="background-color: blue" class="nice_button">Blink LED!</button>
    <script>
      get_request_async("/get_json", load_json)
    </script>
</body>
</html>
)rawliteral";

const char second_page_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
    <title>Another Example Page!</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <script>
    function return_to_main_page() {
        location.href = location.origin;
    }
    </script>
    <link rel="stylesheet" href="/stylesheet">
</head>
<body>
    <h2 style="text-align: center" >Another Example Page!</h2>
    <button onclick="return_to_main_page()" style="background-color: blue" class="nice_button">Return to main page!</button>
</body>
</html>
)rawliteral";

const char stylesheet_css[] PROGMEM = R"rawliteral(
body {
    background-color: grey;
  }

.nice_button {
    border: none;
    color: white;
    padding: 10px 20px;
    text-align: center;
    text-decoration: none;
    display: inline-block;
    font-size: 16px;
    margin: 4px 2px;
    cursor: pointer;
    border-radius: 8px;
}

.roundedDiv {
    border-color: black;
    border-radius: 5px;
    border-style: solid;
    padding: 5px;
    margin: 5px;
}

table {
    font-family: Arial, Helvetica, sans-serif;
    border-collapse: collapse;
    width:100%;
}

table td, table th {
    border: 1px solid #ddd;
    padding: 8px;
}

table tr:nth-child(even){background-color: #f2f2f2;}
table tr:nth-child(odd){background-color: #d5d7d8;}

table tr:hover {background-color: #ddd;}

table th {
    padding-top: 12px;
    padding-bottom: 12px;
    text-align: left;
    background-color: #0073bf;
    color: white;
}
)rawliteral";
#endif