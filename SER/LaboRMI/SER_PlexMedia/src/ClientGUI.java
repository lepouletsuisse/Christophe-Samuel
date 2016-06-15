

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;


public class ClientGUI {
    private static JPanel mainPanel;
    private static RmiClient controleurClient;
    
    private static JLabel warningLabel	= new JLabel();
    private static JLabel errorMessage	= new JLabel();

    private JButton getData 				= null;
    
    public ClientGUI(final RmiClient _controleurClient) {
    	controleurClient = _controleurClient;
    	
        mainPanel = new JPanel();
        
        
        // Définition de la barre d'outils
        getData = new JButton("Get Data");
        getData.addActionListener (new ActionListener(){
            public void actionPerformed(ActionEvent e){
            	controleurClient.getData();
            }
        });
        mainPanel.add(getData);
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                //Turn off metal's use of bold fonts
                UIManager.put("swing.boldMetal", Boolean.FALSE);
                createAndShowGUI();
            }
        });

    }
    private void createAndShowGUI() {
        //Create and set up the window.
        JFrame frame = new JFrame("Client Cinema");

        
        frame.setLocationRelativeTo(null);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        
        frame.setSize(250, 70);
        //Add content to the window.
        frame.setContentPane(mainPanel);
        
        //Display the window.
        frame.setVisible(true);
        frame.setResizable(false);
    }
    
}