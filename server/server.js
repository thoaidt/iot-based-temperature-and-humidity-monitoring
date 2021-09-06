var http = require("http");
var url = require("url");
var querystring = require("querystring");
var db = [];
var fs = require("fs");

function onRequest(request, response){
	
	var urldata = url.parse(request.url);
	var pathname = urldata.pathname;
	var query = urldata.query;
	var querydata = querystring.parse(query);
	
    if(pathname == "/update"){
		var data = {
			temp: querydata.temp,
			humi: querydata.humi
		};
		db.push(data);
		console.log(data);
		response.end(); 
    }

	else if(pathname == "/get"){
		response.writeHead(200, {"Content-Type": "application/json"});
		response.end(JSON.stringify(db));
		db = [];
    }
	
	else{
		fs.readFile("./index.html", function(error, content){
			response.writeHead(200, {"Content-Type": "text/html"});
			response.end(content); 
		})
    }
}

http.createServer(onRequest).listen(8080);
console.log("Server is started at port 8080");