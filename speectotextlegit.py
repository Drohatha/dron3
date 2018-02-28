import speech_recognition as sr
from geometry_msgs.msg import Twist
import rospy

# obtain audio from the microphone
#r = sr.Recognizer()
#with sr.Microphone() as source:
#    print("Say something!")
#    audio = r.listen(source)

# recognize speech using Sphinx
#try:
#    print("Sphinx thinks you said " + r.recognize_sphinx(audio))
#except sr.UnknownValueError:
#    print("Sphinx could not understand audio")
#except sr.RequestError as e:
#    print("Sphinx error; {0}".format(e))


def speech_to_action():
    twist = Twist()
    action1= {'go', "turn"}
    direction = dict()
    magnitude = dict()
    # obtain audio from the microphone
    r = sr.Recognizer()
    with sr.Microphone() as source:
        print("Say something!")
        audio = r.listen(source)

    IBM_USERNAME = "e61ef675-bd60-4241-9556-73e8c7bdbda5"  # IBM Speech to Text usernames are strings of the form XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX
    IBM_PASSWORD = "inIJlpLUKnx1"  # IBM Speech to Text passwords are mixed-case alphanumeric strings
    command =''
    try:
        command = r.recognize_ibm(audio, username=IBM_USERNAME, password=IBM_PASSWORD)
    except sr.UnknownValueError:
        print("IBM Speech to Text could not understand audio")
    except sr.RequestError as e:
        print("Could not request results from IBM Speech to Text service; {0}".format(e))

    print(command)
    command = command.replace('\n','')
    commands = command.split(' ')
    if commands:
        #this is a test
        twist.linear.z = 5.0
        twist.linear.x = 0
        twist.linear.y = 0
    return twist

def do_stuff():
    twist = speech_to_action()
    pub = rospy.Publisher('base_controller/command',twist, queue_size=1)
    rospy.init_node('navn',anonymous=True)
    #rate = rospy.Rate(1)
    while not rospy.is_shutdown():
        twist = speech_to_action()
        pub.publish(twist)
do_stuff()
