#!/usr/bin/env python
# -*- coding: utf-8 -*-

# ======================================================================
#

#
#       oooo                                .o8
#       `888                               "888
#        888  .oooo.    .ooooo.   .ooooo.   888oooo.
#        888 `P  )88b  d88' `"Y8 d88' `88b  d88' `88b
#        888  .oP"888  888       888   888  888   888
#        888 d8(  888  888   .o8 888   888  888   888
#    .o. 88P `Y888""8o `Y8bod8P' `Y8bod8P'  `Y8bod8P'
#    `Y888P
#
#      Job Assistant to Create and Overwrite Backups
#
# ======================================================================
#
#
#   LAST MODIFIED: 1.10.2018
#
#   OMAAN TYÖKÄYTTÖÖN!
#   OHJELMOINTI 1-KURSSIN ALUSTA KAATUI ERÄÄN TARKISTUSURAKAN AIKANA,
#   JA MENETIN KAIKKI TYÖNI. PÄÄTIN OTTAA JOKAISESTA TYÖSTÄ JA SILLE
#   ANTAMASTANI PALAUTTEESTA VARMUUSKOPION TIETOKONEELLE. TÄMÄ
#   OSOITTAUTUI KUITENKIN VAIVALLOISEKSI, JOTEN PÄÄTIN, ETTÄ KIRJOITAN
#   NOPEAN OHJELMAN TALLENTAMAAN JOKAISEN TYÖN SEKÄ PALAUTTEEN OIKEAAN
#   PAIKKAAN.
#
#   OHJELMA, JOKA AUTTAA PITÄMÄÄN KIRJAA OHJELMOINTI 1 TYÖTUNNEISTA.
#   LUO JOKAISESTA PALAUTTEESTA VARMUUSKOPION SEKÄ TALLENTAA
#   TYÖTUNNIT TIEDOSTOON 'time_spent'.
#
#   TARVITSEE KUNNOLLA TOIMIAKSEEN KAKSI .TXT TIEDOSTOA:
#   - time_spent.txt (pitää kirjaa työtunneista)
#   - works_done.txt (ei välttämätön)
#
#   MUISTA SIIRTÄÄ JACOBIN .PY TIEDOSTO SAMAAN KANSIOON, JOHON HALUAT
#   TYÖSI MENEVÄN!

import datetime


def add_to_total_hours(hour, minute):
    """
    Funktio avaa olemassaolevan tiedoston 'time_spent' johon se
    tallentaa päivän kokonaistyöajan.
    :param hour: työtunnit päivältä
    :param minute: työminuutit päivältä
    """

    if hour > 0 or minute > 0:
        time_file = open("time_spent.txt", "a+")
        time_file.write("{}, {} hour(s), {} minute(s).".format(datetime.date.today(),
                                                           hour,
                                                           minute) + "\n")
        time_file.close()
        print()
        print("SUCCESSFULLY SAVED PROGRESS!")

    else:
        print("PROGRESS WAS NOT SAVED!")
        print("It appears your total working hour was 0 hours and 0 minutes.")
        print("There is no point in adding this to the file.")


def add_to_total_works(amount):
    """
    Beta-vaiheessa oleva funktio joka ajaa nyt vaan asiaansa
    Funktio tallettaa päivän aikana tehtyjen töiden lukumäärän
    erilliseen tiedostoon.
    :param amount: päivän aikana tehdyt työt
    """

    file_input_list = []
    with open('works_done.txt') as file:
        for line in file:
            tyot, jakaja, kaikki = line.split(" ")
            file_input_list.append(int(tyot))
            file_input_list.append(int(kaikki))

    open('works_done.txt', 'w').close()
    works_done = file_input_list[0] + amount

    open('works_done.txt', 'w').write(
                "{} / {}".format(works_done, file_input_list[1]))

    return works_done, file_input_list[1]


def is_input_time_okay(user_input, what_type_of_time):
    """
    Funktio tarkistaa, onko käyttäjän syöttämät aikamääreet
    virheettömiä. Syöte tulee olla muodossa HH:MM
    :param user_input: käyttäjän syöte
    :param what_type_of_time: joko 'END' tai 'START'
    :return: palauttaa ohjelmalle tunnit ja minuutit
    """

    while True:
        try:
            hour, minute = user_input.split(":")
            if 00 <= int(hour) < 24 and 00 <= int(minute) < 60:
                break
            else:
                print("Error, incorrect input! (HH:MM)")
                user_input = input("{}ING TIME: (HH:MM): ".format(
                    what_type_of_time.upper()))

        except (TypeError, ValueError):
            print("Error, incorrect input! (HH:MM)")
            user_input = input("{}ING TIME: (HH:MM): "
                               .format(what_type_of_time.upper()))

    return hour, minute


def create_a_new_project(work_number, palaute):
    """
    Luo uuden tiedoston käyttäen aiempaa syötettä 'work_number'.
    Tiedostoon kirjoitetaan käyttäjän syöte, joka tässä tapauksessa
    on grade-helperistä copy-pastattu palaute.
    :param work_number: työn numero, muodossa 'xxxxxx'.
    """
    confirm_file_creation = yes_or_no(input("Do you want to create a new file and save this feedback? (Y/N): "))
    if confirm_file_creation == "Y":
        new_work_file = open("{}.txt".format(work_number), "w+")

        for item in palaute:
            new_work_file.write(item)
            new_work_file.write("\n")

        new_work_file.close()
        print()
        print("Successfully created a new file!")
    else:
        print("Feedback was not saved to a file!")

    return confirm_file_creation

def copy_paste_input():
    """
    Käyttäjän syöttämä palaute tallennetaan listaan
    :return: lista jossa palaute sijaitsee
    """
    print("Copy-paste the feedback below.\n"
          "To stop writing, input 'jacob'.")

    palaute = []

    while True:
        grader_input = input("")
        if grader_input == "jacob":
            break
        else:
            palaute.append(grader_input)

    return palaute


def work_number_inquiry():
    """
    Virhetarkastelua projektin numerolle.
    :return: tarkastelun läpäissyt projektin numero
    """

    while True:

        user_input = input("PROJECT NUMBER (xxxxxx): ")
        if len(str(user_input)) != 6:
            print("Oops, there may be a typo in your input. (Default = 6)")
            input_2 = yes_or_no(input("Do you want to proceed anyway? (Y/N): "))
            if input_2 == "Y":
                return user_input
        else:
            return user_input


def yes_or_no(user_input):
    """
    Virhetarkastelua käyttäjän antamille syötteille.
    :param user_input: käyttäjän syöte
    :return: virhetarkastelun läpäissyt syöte ("Y" tai "N")
    """
    while True:
        if user_input == "Y" or user_input == "N":
            return user_input

        else:
            user_input = input("Type 'Y' for 'YES', 'N' for 'NO': ")


def user_goal():
    """
    Virhetarkastelua tavoitteen syötteelle. Kommentoi myös
    käyttäjän tavoitemääriä.
    :return: virhetarkastelun läpäissyt tavoitemäärä
    """

    while True:
        try:
            user_input = int(input("Goal for the day: "))
            if user_input > 10:
                print("I sure hope you're up for that challenge!")
            elif user_input < 5:
                print("Aww come on, surely you can do better than that!")
            return user_input
        except ValueError:
            print("Goal must be written as an integer!")

def calculate_total_work_hours(s_hour, s_min, e_hour, e_min):
    """
    Laskee yhteen projektiin käytetyn ajan.
    :param s_hour: aloitustunti
    :param s_min: aloitusminuutti
    :param e_hour: lopetustunti
    :param e_min: lopetusminuutti
    :return: käytetty aika tunteina ja minuutteina
    """

    hours_spent = int(e_hour) - int(s_hour)
    minutes_spent = int(e_min) - int(s_min)
    if minutes_spent < 0:
        hours_spent -= 1
        new_minutes = 60+(minutes_spent)
        minutes_spent = new_minutes

    if minutes_spent > 59:
        tunnitminuuteista = int(minutes_spent / 60)
        minuutitjaaneet = (minutes_spent % 60)
        hours_spent += tunnitminuuteista
        minutes_spent = minuutitjaaneet

    print("You spent {} hours and {} minutes on this project.".format(
        hours_spent, minutes_spent))

    return hours_spent, minutes_spent

def read_the_files(wanted_file):
    """
    Jacobin käyttöliittymän ominaisuus. Funktio lukee
    käyttäjän haluamia tiedostoja ja tulostaa niiden
    sisällön ruudulle.
    :param wanted_file: joko time_spent tai projekti
    """
    while True:
        if wanted_file == 1:
            further_inquiry = "time_spent"

        if wanted_file == 2:
            print("Enter the project number (type 'exit' to leave)")
            further_inquiry = input("> ")
            if further_inquiry == "exit":
                return

        print("Opening the file...")
        print("=" * 52)

        try:
            with open("{}.txt".format(further_inquiry)) as file:
                for line in file:
                    line_strip = line.strip()
                    print(line_strip)
            return
        except FileNotFoundError:
            print("File not found!")

def main():

    ##### KIRJAA PITÄVÄT MUUTTUJAT & LISTAT #########################

    total_time = [0, 0]  # Työaika kokonaisuudessaan tältä päivältä
    goal_keeper = 0  # Pitää kirjaa, kuinka monta työtä tänään tehty
    work_progress = open("works_done.txt", "r+").read() #  töiden lkm
    now = datetime.datetime.now()

    ###### OHJELMAN ALOITUSOTSIKKO ##################################

    print("     oooo                                .o8       ")
    print("     `888                               \"888       ")
    print("      888  .oooo.    .ooooo.   .ooooo.   888oooo.  ")
    print("      888 `P  )88b  d88' `\"Y8 d88' `88b  d88' `88b ")
    print("      888  .oP\"888  888       888   888  888   888 ")
    print("      888 d8(  888  888   .o8 888   888  888   888 ")
    print("  .o. 88P  `Y888""8o ` Y8bod8P' `Y8bod8P'  `Y8bod8P' ")
    print("  `Y888P                                           ")



    print("="*52)
    print("   Job Assistant to Create and Overwrite Backups")
    print("="*52)
    print()
    print("This program helps the user to keep track of their")
    print("working hours, as well as the amount of work done.")
    print("The user inputs a copy-paste of the feedback they've")
    print("given to a project, and the program then creates")
    print("a backup .txt file of the input, and saves it to:")
    print("C:/Users/linne/Desktop/Kokeilukansio")
    print()
    print("="*52)
    print("= KEEP THE PROGRAM RUNNING UNTIL YOU STOP WORKING! =")
    print("="*52)
    print("============== PROJECTS DONE: {:7s} ==============".format(work_progress))
    print()
    print("CURRENT TIME AND DATE: {}".format(now.strftime("%H:%M, %Y-%m-%d")))

    #################################################################
    #                                                               #
    #   Ohjelma kysyy käyttäjän tavoitemäärää. Ei mitenkään kovin   #
    #   hyödyllinen tieto, mutta ohjelma ilmoittaa, kun tavoite on  #
    #   saavutettu.                                                 #

    goal = user_goal()

    #################################################################
    #                                                               #
    #   Jacobin käyttöliittymä                                      #
    #   TODO: Kun on aikaa, muokkaa käliä siistimmäksi

    while True:
        print("=" * 52)
        print("[1] NEW PROJECT [2] VIEW WRITTEN FILES [3] EXIT JACOB")
        interface_input = int(input("> "))
        while True:
            if interface_input == 1:

                goal_keeper += 1
                print("=" * 52)
                work_number = work_number_inquiry()
                print("=" * 52)
                #   Aloitusajan kysyminen
                starthour, startminute = is_input_time_okay(
                    input("START TIME (HH:MM): "), "START")
                print("=" * 52)
                #   Palautteen syöttäminen ohjelmalle
                kayttajan_palaute = copy_paste_input()

                #   Palaute luodaan tiedostoksi nimimuodolla "xxxxxx.txt"
                save_changes_or_not = create_a_new_project(work_number,
                                                           kayttajan_palaute)
                if save_changes_or_not == "N":
                    goal_keeper -= 1


                #   Käytetyn ajan laskeminen ja lisääminen kokonaisaikaan
                if save_changes_or_not == "Y":

                    print("=" * 52)
                    #   Lopetusajan kysyminen
                    hour, minute = is_input_time_okay(
                        input("END TIME (HH:MM): "), "END")

                    p_hours, p_minutes = \
                        calculate_total_work_hours(starthour, startminute,
                                                   hour, minute)

                    total_time[0] += p_hours
                    total_time[1] += p_minutes

                    if total_time[1] > 59:
                        tunnitminuuteista = int(total_time[1] / 60)
                        minuutitjaaneet = (total_time[1] % 60)
                        total_time[0] += tunnitminuuteista
                        total_time[1] = minuutitjaaneet

                else:
                    print()
                    print("The amount of time spent to this project was not")
                    print("added to todays total working time, because you've")
                    print("chosen earlier not to save the feedback.")

                    if goal_keeper == goal:
                        print("=" * 52)
                        print("Hey, you've reached your goal! Awesome!")

                break

            elif interface_input == 2:
                print("Which file do you want to read?")
                print("[1] time_spent [2] A project file")
                read_the_files(int(input("> ")))

                break

            elif interface_input == 3:
                continue_option = yes_or_no(input(
                    "Are you sure? (Y/N): "))
                if continue_option == "Y":

                    add_to_total_hours(total_time[0], total_time[1])
                    works_done, total_done = add_to_total_works(goal_keeper)

                    print("=" * 52)
                    print(
                        "TOTAL TIME SPENT TODAY: {} hours and {} minutes"
                            .format(
                            total_time[0], total_time[1]))
                    print("TOTAL WORKS DONE TODAY: {}".format(goal_keeper))
                    print("TOTAL WORKS DONE, ALL TIME: {} / {}".format(works_done,
                                                            total_done))
                    print("PyCharm Community Edition 2017.2.4 can be closed now.")
                    print("=" * 52)

                    return
                break
            else:
                print("Not an available option! ([1], [2], [3]: ")
                interface_input = int(input("> "))

    #################################################################
    #                                                               #
    #   Käyttäjän lopettaessa työt, ohjelma ajaa funktion, joka     #
    #   lisää tiedostoon 'time_spent' päivän kokonaistyöajan        #
    #   muodossa yyyy-mm-dd, x hours, y minutes.                    #

    #################################################################



main()
