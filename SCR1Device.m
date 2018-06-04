(* ::Package:: *)

BeginPackage["SCR1Device`"]


Begin["`Private`"]


DeviceFramework`DeviceClassRegister["SCR1",
"OpenFunction"->open,
"CloseFunction"->close,
"ReadFunction"->read,
"Properties"->{
	"Registers"->Null,
	"pc"->Null}
]


open[]:=Print["Open function placeholder"]


close[]:=Print["Close function placeholder"]


read[]:=Print["Read function placeholder"]


End[]


EndPackage[]
