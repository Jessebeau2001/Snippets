WindowName = destiny2.exe

CollectionPos := [1900, 70]
ArmorWidPos := [1650, 470]
BlueHelmPos := [1400, 350]
HelmSlotPos := [2300, 350]
UpgradePos := [1100, 580]
BlueIndex := 6

^F5:: Reload

F6::
	MouseClick Left, CollectionPos[1], CollectionPos[2]
	Sleep 500
	MouseClick Left, ArmorWidPos[1], ArmorWidPos[2]
	
	; Move 7 tabs down in the armor collections tab
	clicks = 7
	while (clicks >= 0)
	{
		Sleep 125
		Send s
		clicks -= 1
	}
	
	; Move 1 tab right in the leveling armor tab
	Sleep 300
	Send {Right}
	Sleep 600
	
	; Aquire 3x  blue helmet
	MouseMove BlueHelmPos[1], BlueHelmPos[2]
	AquireItem()
	AquireItem()
	AquireItem()
	
	; Exit out of collections and go back to inventory
	Send {Esc}
	Sleep 500
	Send d
	Sleep 500
	Send d
	Sleep 500

	; Masterwork and delete 3x helmet
	MaWoDelHelm(BlueIndex)
	MaWoDelHelm(BlueIndex)
	MaWoDelHelm(BlueIndex)
return

F7::

return

MaWoDelHelm(index) ; Item index: 0 to 8
{
	global HelmSlotPos
	global UpgradePos
	col := Mod(index, 3)
	row := (index - col) / 3

	MouseMove % HelmSlotPos[1], HelmSlotPos[2]
	MouseMove (col + 1) * 145, row * 145, 2, R
	MouseClick Right
	MouseMove % UpgradePos[1], UpgradePos[2]

	Sleep 1200 ; Sleep after opening armor
	ClickHold(3, 2000)
	Send {Esc}
	Sleep 1000

	MouseMove % HelmSlotPos[1], HelmSlotPos[2]
	MouseMove (col + 1) * 145, row * 145, 2, R
	Send {f down}
	Sleep 2500
	Send {f up}
}

ClickHold(amount, time)
{
	while (amount > 0)
	{
		amount--
		Sleep 50
		Click Down
		Sleep time
		Click Up
	}
}

AquireItem()
{
	Sleep 100
	Click Down
	Sleep 4300
	Click Up
	
}

