function doPost(ssid, password){
  var xmlHttp = new XMLHttpRequest();
  var url="/color?brightness=31&red="+red+"&green="+green+"&blue="+blue;
  xmlHttp.open( "GET", url, true );
  xmlHttp.send( null );
}

function connect(event){
  event.returnValue=false;
  return false;
}