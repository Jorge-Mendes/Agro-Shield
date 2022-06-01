Agro-Shield
==============
Arduino Shield (expansion board) for Precision Agriculture (PA). This shield allows to connect multiple commercial sensors, used in the context of the PA, to the Arduino.

Supported Interfaces
---
This Shield supports the connection of sensors with the following outputs:
- SDI-12
- I²C
- 4-20 mA output
- Voltage output
- Frequency output

Dependencies
---
The following libraries are required for the operation of the Agro-Shield:
- FreqPeriod (<a href="http://interface.khm.de/index.php/lab/interfaces-advanced/frequency-measurement-library/" target="_blank">Frequency Measurement Library</a>)
- RTClib (<a href="https://github.com/adafruit/RTClib" target="_blank">Real Time Clock Library</a>)
- Wire (<a href="https://github.com/PaulStoffregen/Wire" target="_blank">Wire Library</a>)
- SDI-12 (<a href="https://github.com/EnviroDIY/Arduino-SDI-12" target="_blank">SDI-12 Library</a>)

PCB
---
<center>
	<table>
		<tr>
			<th colspan="1">Simulated* (Top)</th>
			<th colspan="1">Simulated* (Bottom)</th>
		</tr>
		<tr>
			<td style="text-align:center;"><img alt="Simulated (Top)" src="https://i.ibb.co/xFnn6qp/PCB-SIMUL-FRONT.png" width="315" height="249"/><br><sup>(click on the image to see in full size)</sup></td>
			<td style="text-align:center;"><img alt="Simulated (Bottom)" src="https://i.ibb.co/McNSy31/PCB-SIMUL-BACK.png" width="315" height="249"/><br><sup>(click on the image to see in full size)</sup></td>
		</tr>
	</table>
</center>

<center>
	<table>
		<tr>
			<th colspan="1">Real PCB</th>
		</tr>
		<tr>
			<td style="text-align:center;"><img alt="Real" src="https://i.ibb.co/xFsscR8/PCB-FINAL.jpg" width="315" height="249"/><br><sup>(click on the image to see in full size)</sup></td>
		</tr>
	</table>
</center>

<sup>*Simulation obtained using POV-Ray software: <a href="http://www.povray.org/" target="_blank">povray.org</a></sup>
