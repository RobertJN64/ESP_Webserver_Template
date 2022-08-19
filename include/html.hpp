#include <Arduino.h>

const char index_html[] PROGMEM = R"rawliteral(

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
