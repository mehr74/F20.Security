# socat -d -d TCP4-LISTEN:1337,fork,reuseaddr EXEC:'python3 padding-oracle-server.py',raw,pty,echo=0,stderr


from Crypto.Cipher import AES
import binascii
from secrets import key, flag


def pad(toPad):
    lenToPad = 16 - len(toPad)
    return toPad + (bytes([lenToPad] * lenToPad))

def checkPadding(paddedString):
    if len(paddedString) != 16:
        return False # All strings must be padded to 16 characters!

    paddingLength = paddedString[-1] # How many bytes were appended?
    if paddingLength > 16 or paddingLength == 0: # The padding is wrong! We can append a maximum of 15 characters since our block is only length 16
        return False

    # Check that each appended byte has the same value

    for j in range(15, 15-paddingLength, -1):
        if paddedString[j] != paddingLength:
            return False

    return True


cipher = AES.new(key, AES.MODE_OFB, b"\x00"*16)
paddedFlag = pad(flag)


encryptedflag = cipher.encrypt(paddedFlag)

print(binascii.hexlify(encryptedflag).decode())

while True:
    cipher = AES.new(key, AES.MODE_OFB, b"\x00"*16)

    print("Do you want to send me something?")
    resp = input()

    try:
        data = binascii.unhexlify(resp)
    except Exception:
        print("Please encode your data hexadecimally")
        continue

    if len(data) != 16:
        print("Please send me a single block to decrypt")
        continue

    message = cipher.decrypt(data)

    if not checkPadding(message):
        print("Your data was not correctly padded!")
        continue

    print("Thank you for your amazing message! Greetings!")
