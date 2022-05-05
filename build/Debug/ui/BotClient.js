function info(){
    console.log("host",window.location.host);
    console.log("protocol",window.location.protocol);
}
window.onload = info();

function submitForm() {
    var http = new XMLHttpRequest();
    console.log(window.location.host);
    console.log(window.location.protocol);
    http.open("POST","/api/bot", true);
    http.setRequestHeader("Content-type","application/x-www-form-urlencoded");
    var params = document.getElementById('botInputForm').value; // probably use document.getElementById(...).value
    console.log(params);

    var ul = document.getElementById("messageList");
    var li = document.createElement("li");
    li.classList.add('req');
    li.appendChild(document.createTextNode(params));
    ul.appendChild(li);

    http.send(params);
    http.onload = function() {
        alert(http.responseText);
    }
}
function alert(responseText){
    console.log(responseText)
    var ul = document.getElementById("messageList");
    var li = document.createElement("li");
    li.classList.add('res');
    li.appendChild(document.createTextNode(responseText));
    ul.appendChild(li);
}