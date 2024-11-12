// src/App.js
import React, { useState } from 'react';  // Import React and useState hook
import { initializeApp } from "firebase/app";  // Import Firebase initialization method
import { getDatabase, ref, set } from "firebase/database";  // Import Firebase database methods
import './App.css';  // Import custom CSS for styling

// Firebase configuration object containing all necessary credentials to access the Firebase project
const firebaseConfig = {
    apiKey: "AIzaSyCviV1wN2913TSBepU53r2T4pkDvsnrCgY",
    authDomain: "task7-807a2.firebaseapp.com",
    databaseURL: "https://task7-807a2-default-rtdb.firebaseio.com",
    projectId: "task7-807a2",
    storageBucket: "task7-807a2.appspot.com",
    messagingSenderId: "902656828546",
    appId: "1:902656828546:web:6657df06f838df8c3e009b"
};

// Initialize Firebase with the provided configuration
const app = initializeApp(firebaseConfig);

// Get a reference to the Firebase Realtime Database service
const database = getDatabase(app);

// Functional component to control the traffic light system
const TrafficLightControl = () => {
  // State hook to track the status of the system (such as success or error messages)
  const [status, setStatus] = useState('Firebase initialized successfully');

  // Function to toggle the LED color by sending the selected color to Firebase
  const toggleLED = (color) => {
    // Set the color in the Firebase database under 'ledControl' node
    set(ref(database, 'ledControl'), { color })
      .then(() => 
        // On success, update the status message to indicate the color was toggled
        setStatus(`${color.toUpperCase()} LED toggled`)
      )
      .catch((error) => 
        // On error, update the status message with the error message
        setStatus(`Error: ${error.message}`)
      );
  };

  return (
    <div className="app-container">  // Main container for the app
      <h1 className="heading">Traffic Control System</h1>  // Title of the app
      <div className="control-panel">  // Panel that contains the buttons for controlling the LEDs
        {/* Buttons to toggle the LEDs based on the selected color */}
        <button onClick={() => toggleLED('red')} className="button red-button">Red</button>
        <button onClick={() => toggleLED('green')} className="button green-button">Green</button>
        <button onClick={() => toggleLED('blue')} className="button blue-button">Blue</button>
        <button onClick={() => toggleLED('off')} className="button exit-button">Off</button>
      </div>
      {/* Display the current status or message */}
      <p className="status">{status}</p>
    </div>
  );
};

// Export the TrafficLightControl component so it can be used elsewhere
export default TrafficLightControl;
