# Utility-Service-Provider
COMP3400 Final Project: Utility Service Provider Application
Contributors: Brandon Levack, Jacob Bondy, Matteo Pontoni

Dependencies:
  Graphics Library QT,
  PowerShell for building

Build Instructions: In powershell window, in project main directory, execute ./build.ps1
To execute program: ./uspMain.exe

*TODO
Add a list of customers to the provider class.
Make customer method customer.bill(), which sends the customer a bill and calls customer.reset(), which resets the count for all the utilities they are using
Bill class calculates all the totals based on the flat rates and variable rates of the services
