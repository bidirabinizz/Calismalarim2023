import React, {useState} from 'react'
import "./anasayfa.css"



function anasayfa({loggedInUsername, MailAdress, Admin}) {


    /** Admin Giriş Kontrolü Ayarlandı**/
    function adminGirisKontrol(Admin){
        if(Admin == true){
            <alert>Admin Girişi Yapıldı</alert>
            console.log("başarılı")
        }
        else {
            <alert>Admin Girişi Yapıldı</alert>
            console.log("başarısız")
        }
    }



  return (
    <div className='anasayfadeneme'>
        <br></br>
        <span>Hoşgeldiniz, {loggedInUsername} </span>
        <div>Mail Adres, {MailAdress}</div>
        

        <div>Admin Yetkisi : {Admin ? <span>Admin Girişi Yaptınız</span> : <span>Admin Değilsiniz</span>}</div>
        <button onClick={adminGirisKontrol}>Admin Girişi Test</button>
        
    </div>
  )
}

export default anasayfa



