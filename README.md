# Catmate mate
 ## The backstory ##
 After 7 years of dependable service something went wonky on the controller board for our Catmate C3000. Our cat started to become a fatcat. Not so good. So instead of plonking out $90 for a new automatic cat feeder, I just hooked up an old Arduino to the internal motor. Nothing fancy. It just actuates the motor at a certain time for a certain duration. I didn't want to bother with buttons for resetting the time or an OLED display (I can always just reprogram it), and anyway the *Powers That Be* in the household could not wait for a solution a day longer!
 
 ## The setup ##
 An arduino sketch to dispense cat food in the **CatMate C3000**. The hardware is a standard arduino or compatible with an Adafruit MotorShield 2.0 board to actuate the Catmate C3000 and a DS1307 realtime clock to keep track of time. The DS1307 has a lot of time drift so a Chronodot would be a better solution and should work as a direct swap for the DS1307.
  
 The M1 terminals of the motorshield are conneted to the hobby motor inside the CateMat C3000 (grey and orange wires).
 
 v1.0 - BRC 5/14/2022
