(* ::Package:: *)

BeginPackage["SCR1Device`"]


Begin["`Private`"]


DeviceFramework`DeviceClassRegister["SCR1",
"OpenFunction"->open,
"CloseFunction"->close,
"ReadFunction"->read,
"Properties"->{
	"Registers"->Null,
	"pc"->Null},
"GetPropertyFunction"->(DeviceFramework`DeviceGetProperty[##]&)
]


$string="abcde"


$positions=<||>


read[___] := $Failed


read[{_, h_}] := 
 StringTake[$string, {++$positions[h]}] /; $positions[h] < 5


open[___] := Module[{h = CreateUUID[]}, $positions[h] = 0; h]


close[{_, h_}, ___] := $positions[h] =.


End[]


EndPackage[]
