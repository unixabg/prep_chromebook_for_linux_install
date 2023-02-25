# prep_chromebook_for_linux_install
<p>Use Centipede to help prep chromebook for linux install.<br>
Currently written with Linux workstation in mind.</p>
<h1><b>Usage</b></h1>
<li>Install Arduino IDE
<ul><a href="https://www.arduino.cc/en/Guide/Linux">Arduino IDE webpage</a></ul>
<li>Copy the script.ino file, in this repo, into the IDE
<li>Connect the centipede to your machine.
<li>Upload the code onto the centipede.
<li>Put chromebook in to developer mode.
<li>Once into developer mode, access the terminal.
<li>Log in as chronos user in terminal <code>$: chronos</code>
<li>Escalate using <code>$: sudo su</code>
<li>Plug centipede into chromebook and let it run its commands.

<h1><b>Notes:</b></h1>
<p>Currently if you change the void loop() to an int main() it will lock up the centipede.  I have not yet discovered if it is hard bricked or just locked up.</p>
<p>Used <code>$: flashrom --wp-status</code> and <code>$: flashrom --wp-disable</code> as a test of commands.  Replace with the actual desired commands.

<h2><b>Issues</b></h2>
<li>The Keyboard.print(), Keyboard.println(), Keyboard.press() functions sometimes do not return the full string or list of characters of the complete command. Still looking at why.