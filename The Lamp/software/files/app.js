function doGet(red,green,blue){
  var xmlHttp = new XMLHttpRequest();
  var url="/color?brightness=31&red="+red+"&green="+green+"&blue="+blue;
  xmlHttp.open( "GET", url, true );
  xmlHttp.send( null );
}

function onClickRed(event) {
  doGet(255,0,0);
  event.returnValue=false;
  return false;
}

function onClickGreen(event) {
  doGet(0,255,0);
  event.returnValue=false;
  return false;
}

function onClickBlue(event) {
  doGet(0,0,255);
  event.returnValue=false;
  return false;
}