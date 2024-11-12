
import { initializeApp } from "firebase/app";
import { getDatabase } from "firebase/database";


const firebaseConfig = {
    apiKey: "AIzaSyCviV1wN2913TSBepU53r2T4pkDvsnrCgY",
    authDomain: "task7-807a2.firebaseapp.com",
    projectId: "task7-807a2",
    storageBucket: "task7-807a2.appspot.com",
    messagingSenderId: "902656828546",
    appId: "1:902656828546:web:6657df06f838df8c3e009b"
  };

const app = initializeApp(firebaseConfig);
const database = getDatabase(app);

export default database;
