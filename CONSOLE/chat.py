import json
import os
import numpy as np
from tensorflow import keras
from sklearn.preprocessing import LabelEncoder

import colorama 
colorama.init()
from colorama import Fore, Style, Back

import random
import pickle

with open("intents.json") as file:
    data = json.load(file)


def chat():
    # load trained model
    model = keras.models.load_model('chat_model')

    # load tokenizer object
    with open('tokenizer.pickle', 'rb') as handle:
        tokenizer = pickle.load(handle)

    # load label encoder object
    with open('label_encoder.pickle', 'rb') as enc:
        lbl_encoder = pickle.load(enc)

    # parameters
    max_len = 20
    os.system('cls')
    print(Fore.YELLOW + "Start messaging with Chappie (type quit to stop)!" + Style.RESET_ALL)
    print(Fore.GREEN + "Chappie :" + Style.RESET_ALL + " Hello! I'm Chappie! Note that my responses are limited!")
    

    while True:
        print(Fore.LIGHTBLUE_EX + "User : " + Style.RESET_ALL, end="")
        inp = input()
        if inp.lower() == "quit":
            break

        result = model.predict(keras.preprocessing.sequence.pad_sequences(tokenizer.texts_to_sequences([inp]), truncating='post', maxlen=max_len))
        tag = lbl_encoder.inverse_transform([np.argmax(result)])

        for i in data['intents']:
            if i['tag'] == tag:
                if np.random.choice(i['responses']) == "open img":
                    os.system('brainlet.png')
                else:
                     print(Fore.GREEN + "Chappie :" + Style.RESET_ALL, np.random.choice(i['responses']))
        # print(Fore.GREEN + "ChatBot:" + Style.RESET_ALL,random.choice(responses))
        
chat()
