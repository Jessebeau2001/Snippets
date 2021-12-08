tagJesse := ""
tagVincent := ""
tagSomeone := ""
tagArie := ""

mailVincent := ""

^F5::Reload

^p::
SapVerify(tagJesse)
return

^Numpad1::
	send %mailVincent%
return

SapVerify(userLoginTag) {
	send %userLoginTag%
	send {return}
}

GUITest()
{

}
