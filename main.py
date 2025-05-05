# Login System by Night
users = {
    "Night": "Test0101",
    "Euel" : "euel2006"
}


def login(uname, pword):
    if uname in users and users[uname] == pword:
        print("\nLogin Success")
        return True
    else:
        print("\nInvalid Username or Password")
        return False

def main():
    print("Please Login\n")
    

    while True:
        uname = input("Enter Username: ").strip()
        if uname == "":
            print("Username cannot be empty. Please try again.\n")
        else:
            break

    while True:
        pword = input("Enter Password: ").strip()
        if pword == "":
            print("Password cannot be empty. Please try again.\n")
        else:
            break

    if login(uname, pword):
        print("Access Granted.\n")
    else:
        print("Access Denied.\n")

main()
print(users)



