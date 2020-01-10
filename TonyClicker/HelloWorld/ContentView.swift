//
//  ContentView.swift
//  HelloWorld
//
//  Created by Nathan Vasquez on 11/7/19.
//  Copyright © 2019 Nathan Vasquez. All rights reserved.
//

import SwiftUI

struct ContentView: View {
    @State var count: Int = 0;
    var body: some View {
        ZStack{
            Color.black
                .edgesIgnoringSafeArea(.all)
            VStack() {
                Text("Tony Clicker!")
                    .bold()
                
                   
                    
                    
                    
                Spacer()
                Text("count: \(count)")
                    .bold()
    
                Spacer()
                Button(action: {
                    self.count += 1
                }) {
                    Image("tony")
                    .renderingMode(.original)
                    .resizable()
                    .scaledToFit()
                    .clipShape(Circle())
                }
                Spacer()
            }
        
            .foregroundColor(.white).font(/*@START_MENU_TOKEN@*/.largeTitle/*@END_MENU_TOKEN@*/)

        }
        
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
