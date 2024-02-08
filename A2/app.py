import tkinter as tk
import pickle
from tkinter import messagebox
import webbrowser
from datetime import datetime
import re


class RegType(tk.Frame):
    def __init__(self, parent, controller):
        tk.Frame.__init__(self, parent)

        self.TITLE = tk.Label(self, text="REG TYPE", font=("Arial", 15, "bold"))
        self.TITLE.place(x=350, y=10)

        self.PROF_BUTTON = tk.Button(
            self,
            text="PROFESSOR",
            font=("Arial", 12, "bold"),
            command=lambda: controller.show_frame(ProfReg),
        )
        self.PROF_BUTTON.place(x=350, y=110)

        self.PG_BUTTON = tk.Button(
            self,
            text="POST GRADUATE",
            font=("Arial", 12, "bold"),
            command=lambda: controller.show_frame(PGReg),
        )
        self.PG_BUTTON.place(x=350, y=210)

        UG_BUTTON = tk.Button(
            self,
            text="UNDER GRADUATE",
            font=("Arial", 12, "bold"),
            command=lambda: controller.show_frame(UGReg),
        )
        UG_BUTTON.place(x=350, y=310)

        Button = tk.Button(
            self,
            text="Back to Login",
            font=("Arial", 12, "bold"),
            command=lambda: controller.show_frame(Login),
        )
        Button.place(x=100, y=500)


class PersonReg(tk.Frame):
    def __init__(self, parent, controller):
        tk.Frame.__init__(self, parent)

        self.AttributesList = []

        self.NAME_PLACE = tk.Label(self, text="Name: ", font=("Arial", 12, "bold"))
        self.NAME_PLACE.place(x=200, y=100)
        self.NAME = tk.Entry(self, width=30, bd=5)
        self.AttributesList.append(self.NAME)
        self.NAME.place(x=400, y=100)

        self.PW_PLACE = tk.Label(self, text="Password: ", font=("Arial", 12, "bold"))
        self.PW_PLACE.place(x=200, y=200)
        self.PW = tk.Entry(self, width=30, bd=5)
        self.AttributesList.append(self.PW)
        self.PW.place(x=400, y=200)

        self.PW2_PLACE = tk.Label(
            self, text="Confirm Password: ", font=("Arial", 12, "bold")
        )
        self.PW2_PLACE.place(x=200, y=300)
        self.PW2 = tk.Entry(self, width=30, bd=5)
        self.AttributesList.append(self.PW2)
        self.PW2.place(x=400, y=300)

        self.EMAIL_PLACE = tk.Label(self, text="Email ID: ", font=("Arial", 12, "bold"))
        self.EMAIL_PLACE.place(x=200, y=400)
        self.EMAIL = tk.Entry(self, width=30, bd=5)
        self.AttributesList.append(self.EMAIL)
        self.EMAIL.place(x=400, y=400)

        self.WEB_PLACE = tk.Label(self, text="WEB: ", font=("Arial", 12, "bold"))
        self.WEB_PLACE.place(x=200, y=500)
        self.WEB = tk.Entry(self, width=30, bd=5)
        self.AttributesList.append(self.WEB)
        self.WEB.place(x=400, y=500)

        Button = tk.Button(
            self,
            text="Login",
            font=("Arial", 12, "bold"),
            command=lambda: controller.show_frame(Login),
        )
        Button.place(x=850, y=600)

    def PW_verification(self):
        password_pattern = re.compile(
            r"^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[!@#$%&*])[^\s]{8,12}$"
        )

        if password_pattern.match(self.PW.get()):
            pass
        else:
            messagebox.showwarning(
                "PASSWORD ERROR",
                "a) It should be within 8-12 character long.\nb) It should contain at least one upper case, one digit, and one lower case.\nc) It should contains one or more special character(s) from the list [! @ # $ % & *]\n d) No blank space will be allowed.",
            )

            return False

        if self.PW.get() != self.PW2.get():
            messagebox.showwarning("PASSWORD ERROR", "Passwords do not match!")
            return False

        else:
            return True

    def email_verification(self):
        pattern = r"^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$"
        if re.match(pattern, self.EMAIL.get()) is not None:
            return True

        else:
            messagebox.showwarning("Invalid Email", "Please enter a valid Email")
            return False


class ProfReg(PersonReg):
    def __init__(self, parent, controller):
        super().__init__(parent, controller)

        self.TITLE = tk.Label(self, text="PROFESSOR REG", font=("Arial", 15, "bold"))
        self.TITLE.place(x=400, y=10)

        self.RES_PLACE = tk.Label(
            self, text="Research Interests: ", font=("Arial", 12, "bold")
        )
        self.RES_PLACE.place(x=200, y=600)
        self.RESEARCH = tk.Entry(self, width=30, bd=5)
        self.AttributesList.append(self.RESEARCH)
        self.RESEARCH.place(x=400, y=600)

        Button = tk.Button(
            self,
            text="Next",
            font=("Arial", 12, "bold"),
            command=lambda: self.register(parent, controller),
        )
        Button.place(x=650, y=600)

    def register(self, parent, controller):
        if not self.PW_verification() or not self.email_verification():
            return

        uid = datetime.now().strftime("%S.%f")[-6:]

        try:
            dbfile = open("database.pkl", "rb")
            db = pickle.load(dbfile)

        except:
            dbfile = open("database.pkl", "wb")
            db = {}
        db[uid] = {
            "name": self.NAME.get(),
            "password": self.PW.get(),
            "email": self.EMAIL.get(),
            "WEB": self.WEB.get(),
            "research": self.RESEARCH.get(),
        }
        dbfile.close()

        dbfile = open("database.pkl", "wb")
        pickle.dump(db, dbfile)
        print(db)

        dbfile.close()

        for item in self.AttributesList:
            item.delete(0, tk.END)

        frame = Home(parent, uid, controller)
        frame.grid(row=0, column=0, sticky="nsew")
        frame.tkraise()


class StuReg(PersonReg):
    def __init__(self, parent, controller):
        super().__init__(parent, controller)

        self.ROLL_NO_PLACE = tk.Label(self, text="RollNo: ", font=("Arial", 12, "bold"))
        self.ROLL_NO_PLACE.place(x=200, y=600)
        self.ROLL_NO = tk.Entry(self, width=30, bd=5)
        self.AttributesList.append(self.ROLL_NO)
        self.ROLL_NO.place(x=400, y=600)

        self.CGPA_PLACE = tk.Label(self, text="CGPA: ", font=("Arial", 12, "bold"))
        self.CGPA_PLACE.place(x=200, y=700)
        self.CGPA = tk.Entry(self, width=30, bd=5)
        self.AttributesList.append(self.CGPA)
        self.CGPA.place(x=400, y=700)

        self.HALL_PLACE = tk.Label(self, text="Hall: ", font=("Arial", 12, "bold"))
        self.HALL_PLACE.place(x=200, y=800)
        self.HALL = tk.Entry(self, width=30, bd=5)
        self.AttributesList.append(self.HALL)
        self.HALL.place(x=400, y=800)


class PGReg(StuReg):
    def __init__(self, parent, controller):
        super().__init__(parent, controller)

        self.TITLE = tk.Label(self, text="PG REG", font=("Arial", 15, "bold"))
        self.TITLE.place(x=400, y=10)

        self.THESIS_PLACE = tk.Label(self, text="Thesis: ", font=("Arial", 12, "bold"))
        self.THESIS_PLACE.place(x=200, y=900)
        self.THESIS = tk.Entry(self, width=30, bd=5)
        self.AttributesList.append(self.THESIS)
        self.THESIS.place(x=400, y=900)

        self.PROF_PLACE = tk.Label(self, text="Advisor: ", font=("Arial", 12, "bold"))
        self.PROF_PLACE.place(x=200, y=1000)
        self.PROF = tk.Entry(self, width=30, bd=5)
        self.AttributesList.append(self.PROF)
        self.PROF.place(x=400, y=1000)
        Button = tk.Button(
            self,
            text="Next",
            font=("Arial", 12, "bold"),
            command=lambda: self.register(parent, controller),
        )
        Button.place(x=650, y=600)

    def register(self, parent, controller):
        if not self.PW_verification() or not self.email_verification():
            return

        uid = datetime.now().strftime("%S.%f")[-6:]

        try:
            dbfile = open("database.pkl", "rb")
            db = pickle.load(dbfile)

        except:
            dbfile = open("database.pkl", "wb")
            db = {}
        db[uid] = {
            "name": self.NAME.get(),
            "password": self.PW.get(),
            "email": self.EMAIL.get(),
            "WEB": self.WEB.get(),
            "RollNo": self.ROLL_NO.get(),
            "Hall": self.HALL.get(),
            "CGPA": self.CGPA.get(),
            "Thesis": self.THESIS.get(),
            "Advisor": self.PROF.get(),
        }

        dbfile.close()

        dbfile = open("database.pkl", "wb")
        pickle.dump(db, dbfile)
        print(db)

        dbfile.close()

        for item in self.AttributesList:
            item.delete(0, tk.END)

        frame = Home(parent, uid, controller)
        frame.grid(row=0, column=0, sticky="nsew")
        frame.tkraise()


class UGReg(StuReg):
    def __init__(self, parent, controller):
        super().__init__(parent, controller)

        self.TITLE = tk.Label(self, text="UG REG", font=("Arial", 15, "bold"))
        self.TITLE.place(x=400, y=10)

        self.FUTURE_PLACE = tk.Label(self, text="Career: ", font=("Arial", 12, "bold"))
        self.FUTURE_PLACE.place(x=200, y=900)
        self.FUTURE = tk.Entry(self, width=30, bd=5)
        self.AttributesList.append(self.FUTURE)
        self.FUTURE.place(x=400, y=900)

        self.CLUB_PLACE = tk.Label(self, text="Societies: ", font=("Arial", 12, "bold"))
        self.CLUB_PLACE.place(x=200, y=1000)
        self.CLUB = tk.Entry(self, width=30, bd=5)
        self.AttributesList.append(self.CLUB)
        self.CLUB.place(x=400, y=1000)
        Button = tk.Button(
            self,
            text="Next",
            font=("Arial", 12, "bold"),
            command=lambda: self.register(parent, controller),
        )
        Button.place(x=650, y=600)

    def register(self, parent, controller):
        if not self.PW_verification() or not self.email_verification():
            return
        uid = datetime.now().strftime("%S.%f")[-6:]

        try:
            dbfile = open("database.pkl", "rb")
            db = pickle.load(dbfile)

        except:
            dbfile = open("database.pkl", "wb")
            db = {}
        db[uid] = {
            "name": self.NAME.get(),
            "password": self.PW.get(),
            "email": self.EMAIL.get(),
            "WEB": self.WEB.get(),
            "RollNo": self.ROLL_NO.get(),
            "Hall": self.HALL.get(),
            "CGPA": self.CGPA.get(),
            "Career": self.FUTURE.get(),
            "Societies": self.CLUB.get(),
        }

        dbfile.close()

        dbfile = open("database.pkl", "wb")
        pickle.dump(db, dbfile)
        print(db)

        dbfile.close()

        for item in self.AttributesList:
            item.delete(0, tk.END)

        frame = Home(parent, uid, controller)
        frame.grid(row=0, column=0, sticky="nsew")
        frame.tkraise()


class Home(tk.Frame):
    def __init__(self, parent, uid, controller):
        tk.Frame.__init__(self, parent)

        self.TITLE = tk.Label(self, text="HOME PAGE", font=("Arial", 15, "bold"))
        self.TITLE.place(x=400, y=10)

        dbfile = open("database.pkl", "rb")
        y = 50
        data = pickle.load(dbfile)
        if uid in data.keys():
            for key, value in data[uid].items():
                if key != "WEB":
                    ELEMENT = tk.Label(
                        self, text=f"{key} : {value}", font=("Arial", 20, "bold")
                    )
                    ELEMENT.place(x=300, y=y)

                else:
                    ELEMENT = tk.Label(
                        self, text=f"{key} : ", font=("Arial", 20, "bold")
                    )
                    ELEMENT.place(x=300, y=y)

                    self.link_text = tk.Text(
                        self,
                        height=1,
                        width=30,
                        wrap="none",
                        borderwidth=0,
                        highlightthickness=0,
                    )
                    self.link_text.insert("1.0", value)
                    self.link_text.tag_configure(
                        "hyperlink", foreground="blue", underline=True
                    )
                    self.link_text.tag_add("hyperlink", "1.0", "1.end")
                    self.link_text.tag_bind(
                        "hyperlink",
                        "<Button-1>",
                        self.open_link,
                    )
                    self.link_text.place(x=400, y=y)

                y = y + 50

            ELEMENT = tk.Label(self, text=f"UID : {uid}", font=("Arial", 20, "bold"))
            ELEMENT.place(x=300, y=y)
            y = y + 100

        dbfile.close()

        Button = tk.Button(
            self,
            text="Logout",
            font=("Arial", 12, "bold"),
            command=lambda: controller.show_frame(Login),
        )
        Button.place(x=600, y=y)

        Button2 = tk.Button(
            self,
            text="Edit",
            font=("Arial", 12, "bold"),
            command=lambda: self.render_edit(parent, uid, controller),
        )
        Button2.place(x=400, y=y)

    def open_link(self, event):
        webbrowser.open_new(self.link_text.get("1.0", "end-1c"))

    def render_edit(self, parent, uid, controller):
        frame = Edit(parent, controller, uid)
        frame.grid(row=0, column=0, sticky="nsew")
        frame.tkraise()


class Edit(tk.Frame):
    def __init__(self, parent, controller, uid):
        tk.Frame.__init__(self, parent)

        self.TITLE = tk.Label(self, text="EDIT DATA", font=("Arial", 15, "bold"))
        self.TITLE.place(x=400, y=10)

        dbfile = open("database.pkl", "rb")
        y = 50
        self.attributes = {}

        data = pickle.load(dbfile)
        if uid in data.keys():
            for key, value in data[uid].items():
                ELEMENT = tk.Label(self, text=f"{key}: ", font=("Arial", 20, "bold"))
                ELEMENT.place(x=300, y=y)

                self.attributes[key] = tk.Entry(self, width=30, bd=5)
                self.attributes[key].place(x=550, y=y)
                self.attributes[key].insert(1, value)
                y = y + 50
            ELEMENT = tk.Label(self, text=f"UID : {uid}", font=("Arial", 20, "bold"))
            ELEMENT.place(x=300, y=y)

        dbfile.close()

        Button = tk.Button(
            self,
            text="Save",
            font=("Arial", 12, "bold"),
            command=lambda: self.save_attributes(uid, parent, controller),
        )
        Button.place(x=650, y=650)

        Button2 = tk.Button(
            self,
            text="Home",
            font=("Arial", 12, "bold"),
            command=lambda: self.render_home(parent, uid, controller),
        )
        Button2.place(x=450, y=650)

    def render_home(self, parent, uid, controller):
        frame = Home(parent, uid, controller)
        frame.grid(row=0, column=0, sticky="nsew")
        frame.tkraise()

    def save_attributes(self, uid, parent, controller):
        dbfile = open("database.pkl", "rb")

        attributes = {}

        data = pickle.load(dbfile)
        if uid in list(data.keys()):
            for key, value in data[uid].items():
                if key == "password":
                    password_pattern = re.compile(
                        r"^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[!@#$%&*])[^\s]{8,12}$"
                    )
                    if not password_pattern.match(self.attributes[key].get()):
                        messagebox.showwarning(
                            "PASSWORD ERROR",
                            "a) It should be within 8-12 character long.\nb) It should contain at least one upper case, one digit, and one lower case.\nc) It should contains one or more special character(s) from the list [! @ # $ % & *]\n d) No blank space will be allowed.",
                        )
                        return
                if key == "email":
                    pattern = r"^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$"
                    if not re.match(pattern, self.attributes[key].get()):
                        messagebox.showwarning(
                            "Invalid Email", "Please enter a valid Email"
                        )
                        return

                data[uid][key] = self.attributes[key].get()
        attributes.update(data)

        dbfile.close()

        dbfile = open("database.pkl", "wb")

        pickle.dump(attributes, dbfile)

        dbfile.close()

        self.render_home(parent, uid, controller)


class DeReg(tk.Frame):
    def __init__(self, parent, controller):
        tk.Frame.__init__(self, parent)

        self.TITLE = tk.Label(
            self, text="DEREGISTER ACCOUNT", font=("Arial", 15, "bold")
        )
        self.TITLE.place(x=400, y=10)

        self.UIDLabel = tk.Label(self, text="UID", font=("Arial", 12, "bold"))
        self.UIDLabel.place(x=100, y=100)
        self.UID = tk.Entry(self, width=30, bd=5)
        self.UID.place(x=300, y=100)

        self.NameLabel = tk.Label(self, text="User Name", font=("Arial", 12, "bold"))
        self.NameLabel.place(x=100, y=200)
        self.NameInput = tk.Entry(self, width=30, bd=5)
        self.NameInput.place(x=300, y=200)

        self.PWLabel = tk.Label(self, text="Password", font=("Arial", 12, "bold"))
        self.PWLabel.place(x=100, y=300)
        self.PWInput = tk.Entry(self, width=30, bd=5)
        self.PWInput.place(x=300, y=300)

        Button = tk.Button(
            self,
            text="De-Register",
            font=("Arial", 12, "bold"),
            command=lambda: self.PWCheck(
                self.UID.get(),
                self.PWInput.get(),
                self.NameInput.get(),
                parent,
                controller,
            ),
        )
        Button.place(x=650, y=450)

        Button2 = tk.Button(
            self,
            text="Register",
            font=("Arial", 12, "bold"),
            command=lambda: controller.show_frame(Login),
        )
        Button2.place(x=650, y=550)

    def PWCheck(self, uid, PW, name, parent, controller):
        dbfile = open("database.pkl", "rb")
        try:
            data = pickle.load(dbfile)

            if uid in list(data.keys()):
                if data[uid]["password"] == PW and data[uid]["name"] == name:
                    self.DeRegCheck(controller, parent, uid)

                else:
                    messagebox.showwarning("CREDENTIALS ERROR", "Credential Mismatch!")
        except EOFError:
            return

        dbfile.close()

    def DeRegCheck(self, controller, parent, uid):
        dbfile = open("database.pkl", "rb")
        try:
            data = pickle.load(dbfile)

            if uid in list(data.keys()):
                del data[uid]

        except EOFError:
            return

        print("here", uid)

        dbfile.close()

        dbfile = open("database.pkl", "wb")

        if len(data) == 0:
            dbfile.close()

        else:
            pickle.dump(data, dbfile)
            dbfile.close()

        controller.show_frame(Login)


class Login(DeReg):
    def __init__(self, parent, controller):
        tk.Frame.__init__(self, parent)

        self.TITLE = tk.Label(self, text="LOGIN", font=("Arial", 15, "bold"))
        self.TITLE.place(x=500, y=10)

        self.AttributesList = []

        self.UIDLabel = tk.Label(self, text="UID", font=("Arial", 12, "bold"))
        self.UIDLabel.place(x=250, y=100)
        self.UID = tk.Entry(self, width=30, bd=5)
        self.UID.place(x=400, y=100)
        self.AttributesList.append(self.UID)

        self.NameLabel = tk.Label(self, text="User Name", font=("Arial", 12, "bold"))
        self.NameLabel.place(x=250, y=200)
        self.Name = tk.Entry(self, width=30, bd=5)
        self.AttributesList.append(self.Name)
        self.Name.place(x=400, y=200)

        self.PWLabel = tk.Label(self, text="Password", font=("Arial", 12, "bold"))
        self.PWLabel.place(x=250, y=300)
        self.PW = tk.Entry(self, width=30, bd=5)
        self.AttributesList.append(self.PW)
        self.PW.place(x=400, y=300)

        Button = tk.Button(
            self,
            text="Login",
            font=("Arial", 12, "bold"),
            command=lambda: self.LoginCheck(parent, controller),
        )
        Button.place(x=250, y=450)

        Button2 = tk.Button(
            self,
            text="Register",
            font=("Arial", 12, "bold"),
            command=lambda: controller.show_frame(RegType),
        )
        Button2.place(x=400, y=450)

        Button3 = tk.Button(
            self,
            text="DeRegister",
            font=("Arial", 12, "bold"),
            command=lambda: controller.show_frame(DeReg),
        )
        Button3.place(x=600, y=450)

        self.strike = 3

    def LoginCheck(self, parent, controller):
        boolean = False
        UIDExists = False

        try:
            dbfile = open("database.pkl", "rb")
            data = pickle.load(dbfile)

        except:
            dbfile = open("database.pkl", "wb")
            data = {}

        print(data)

        if self.UID.get() in list(data.keys()):
            UIDExists = True

            if (
                data[self.UID.get()]["name"] == self.Name.get()
                and data[self.UID.get()]["password"] == self.PW.get()
            ):
                boolean = True
            else:
                boolean = False
                print("[INCORRECT INPUT]")

        dbfile.close()

        if not UIDExists:
            messagebox.showwarning(
                "LOGIN ERROR", "USER ID DOES NOT EXIST, PLEASE REGISTER"
            )
            controller.show_frame(Login)
        else:
            if boolean:
                print(self.UID.get())
                frame = Home(parent, self.UID.get(), controller)
                frame.grid(row=0, column=0, sticky="nsew")
                frame.tkraise()
            else:
                self.strike = self.strike - 1
                if self.strike > 0:
                    messagebox.showwarning(
                        "Limited Trials", f"You have {self.strike} attempts left"
                    )

                if self.strike <= 0:
                    print("[TOO MANY ATTEMPTS , USER DEREGISTERED")
                    messagebox.showwarning(
                        "Limited Trials", f"[TOO MANY ATTEMPTS , USER DEREGISTERED"
                    )
                    self.DeRegCheck(controller, parent, self.UID.get())

                    controller.show_frame(RegType)
                return

        for item in self.AttributesList:
            item.delete(0, tk.END)

        return


class Application(tk.Tk):
    def __init__(self, *args, **kwargs):
        tk.Tk.__init__(self, *args, **kwargs)

        window = tk.Frame(self)
        window.pack()

        window.grid_rowconfigure(0, minsize=1000)
        window.grid_columnconfigure(0, minsize=1000)

        self.frames = {}
        for F in (Login, ProfReg, PGReg, RegType, UGReg, StuReg, DeReg):
            frame = F(window, self)
            self.frames[F] = frame
            frame.grid(row=0, column=0, sticky="nsew")

        self.show_frame(Login)

    def show_frame(self, page):
        frame = self.frames[page]
        frame.tkraise()


app = Application()
app.mainloop()
