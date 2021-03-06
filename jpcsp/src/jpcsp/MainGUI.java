/*
This file is part of jpcsp.

Jpcsp is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Jpcsp is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Jpcsp.  If not, see <http://www.gnu.org/licenses/>.
 */

package jpcsp;

import jpcsp.GUI.SettingsGUI;
import jpcsp.GUI.MemStickBrowser;
import java.awt.Dimension;
import java.awt.Insets;
import java.awt.Point;
import java.awt.event.ComponentEvent;
import java.awt.event.ComponentListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.io.File;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.nio.ByteBuffer;
import java.nio.channels.FileChannel;
import javax.swing.JFileChooser;
import javax.swing.JOptionPane;
import javax.swing.JPopupMenu;
import javax.swing.ToolTipManager;
import javax.swing.UIManager;
import jpcsp.Debugger.ConsoleWindow;
import jpcsp.Debugger.DisassemblerModule.DisassemblerFrame;
import jpcsp.Debugger.ElfHeaderInfo;
import jpcsp.Debugger.InstructionCounter;
import jpcsp.Debugger.MemoryViewer;
import jpcsp.GUI.UmdBrowser;
import jpcsp.HLE.pspdisplay;
import jpcsp.HLE.pspiofilemgr;
import jpcsp.util.JpcspDialogManager;
import jpcsp.util.MetaInformation;
import jpcsp.filesystems.umdiso.*;
import jpcspd.format.PSF;

/**
 *
 * @author  shadow
 */
public class MainGUI extends javax.swing.JFrame implements KeyListener, ComponentListener {
    final String version = MetaInformation.FULL_NAME;
    ConsoleWindow consolewin;
    DisassemblerFrame disasm;
    ElfHeaderInfo elfheader;
    MemoryViewer memoryview;
    SettingsGUI setgui;
    MemStickBrowser memstick;
    Emulator emulator;
    UmdBrowser umdbrowser;
    InstructionCounter instructioncounter;
    private Point mainwindowPos; // stores the last known window position
    private boolean snapConsole = true;

    /** Creates new form MainGUI */
    public MainGUI() {
        emulator = new Emulator(this);

        /*next two lines are for overlay menus over joglcanvas*/
        JPopupMenu.setDefaultLightWeightPopupEnabled(false);
        ToolTipManager.sharedInstance().setLightWeightPopupEnabled(false);
        //end of

        initComponents();
        int pos[] = Settings.get_instance().readWindowPos("mainwindow");
        setLocation(pos[0], pos[1]);
        setTitle(version);

        /*add glcanvas to frame and pack frame to get the canvas size*/
        getContentPane().add(pspdisplay.get_instance(), java.awt.BorderLayout.CENTER);
        pspdisplay.get_instance().addKeyListener(this);
        this.addComponentListener(this);
        pack();
        
        Insets insets = this.getInsets();
        Dimension minSize = new Dimension(
            480 + insets.left + insets.right,
            272 + insets.top + insets.bottom);
        this.setMinimumSize(minSize);

        //logging console window stuff
        consolewin = new ConsoleWindow();
        snapConsole = Settings.get_instance().readBoolOptions("guisettings/snapLogwindow");
        if (snapConsole) {
            mainwindowPos = getLocation();
            consolewin.setLocation(mainwindowPos.x, mainwindowPos.y + getHeight());
        } else {
            pos = Settings.get_instance().readWindowPos("logwindow");
            consolewin.setLocation(pos[0], pos[1]);
        }
    }

    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jToolBar1 = new javax.swing.JToolBar();
        RunButton = new javax.swing.JToggleButton();
        PauseButton = new javax.swing.JToggleButton();
        ResetButton = new javax.swing.JButton();
        MenuBar = new javax.swing.JMenuBar();
        FileMenu = new javax.swing.JMenu();
        openUmd = new javax.swing.JMenuItem();
        OpenFile = new javax.swing.JMenuItem();
        OpenMemStick = new javax.swing.JMenuItem();
        ExitEmu = new javax.swing.JMenuItem();
        EmulationMenu = new javax.swing.JMenu();
        RunEmu = new javax.swing.JMenuItem();
        PauseEmu = new javax.swing.JMenuItem();
        ResetEmu = new javax.swing.JMenuItem();
        OptionsMenu = new javax.swing.JMenu();
        SetttingsMenu = new javax.swing.JMenuItem();
        DebugMenu = new javax.swing.JMenu();
        EnterDebugger = new javax.swing.JMenuItem();
        EnterMemoryViewer = new javax.swing.JMenuItem();
        ToggleConsole = new javax.swing.JMenuItem();
        ElfHeaderViewer = new javax.swing.JMenuItem();
        InstructionCounter = new javax.swing.JMenuItem();
        HelpMenu = new javax.swing.JMenu();
        About = new javax.swing.JMenuItem();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setMinimumSize(new java.awt.Dimension(480, 272));
        addWindowListener(new java.awt.event.WindowAdapter() {
            public void windowClosing(java.awt.event.WindowEvent evt) {
                formWindowClosing(evt);
            }
        });

        jToolBar1.setFloatable(false);
        jToolBar1.setRollover(true);

        RunButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/jpcsp/icons/PlayIcon.png"))); // NOI18N
        RunButton.setText("Run");
        RunButton.setFocusable(false);
        RunButton.setHorizontalTextPosition(javax.swing.SwingConstants.RIGHT);
        RunButton.setIconTextGap(2);
        RunButton.setVerticalTextPosition(javax.swing.SwingConstants.BOTTOM);
        RunButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                RunButtonActionPerformed(evt);
            }
        });
        jToolBar1.add(RunButton);

        PauseButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/jpcsp/icons/PauseIcon.png"))); // NOI18N
        PauseButton.setText("Pause");
        PauseButton.setFocusable(false);
        PauseButton.setHorizontalTextPosition(javax.swing.SwingConstants.RIGHT);
        PauseButton.setIconTextGap(2);
        PauseButton.setVerticalTextPosition(javax.swing.SwingConstants.BOTTOM);
        PauseButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                PauseButtonActionPerformed(evt);
            }
        });
        jToolBar1.add(PauseButton);

        ResetButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/jpcsp/icons/StopIcon.png"))); // NOI18N
        ResetButton.setText("Reset");
        ResetButton.setFocusable(false);
        ResetButton.setHorizontalTextPosition(javax.swing.SwingConstants.RIGHT);
        ResetButton.setIconTextGap(2);
        ResetButton.setVerticalTextPosition(javax.swing.SwingConstants.BOTTOM);
        ResetButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                ResetButtonActionPerformed(evt);
            }
        });
        jToolBar1.add(ResetButton);

        getContentPane().add(jToolBar1, java.awt.BorderLayout.NORTH);

        FileMenu.setText("File");

        openUmd.setText("Load UMD ");
        openUmd.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                openUmdActionPerformed(evt);
            }
        });
        FileMenu.add(openUmd);

        OpenFile.setText("Load File");
        OpenFile.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                OpenFileActionPerformed(evt);
            }
        });
        FileMenu.add(OpenFile);

        OpenMemStick.setText("Load MemStick");
        OpenMemStick.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                OpenMemStickActionPerformed(evt);
            }
        });
        FileMenu.add(OpenMemStick);

        ExitEmu.setText("Exit");
        ExitEmu.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                ExitEmuActionPerformed(evt);
            }
        });
        FileMenu.add(ExitEmu);

        MenuBar.add(FileMenu);

        EmulationMenu.setText("Emulation");

        RunEmu.setText("Run");
        RunEmu.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                RunEmuActionPerformed(evt);
            }
        });
        EmulationMenu.add(RunEmu);

        PauseEmu.setText("Pause");
        PauseEmu.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                PauseEmuActionPerformed(evt);
            }
        });
        EmulationMenu.add(PauseEmu);

        ResetEmu.setText("Reset");
        ResetEmu.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                ResetEmuActionPerformed(evt);
            }
        });
        EmulationMenu.add(ResetEmu);

        MenuBar.add(EmulationMenu);

        OptionsMenu.setText("Options");

        SetttingsMenu.setText("Settings");
        SetttingsMenu.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                SetttingsMenuActionPerformed(evt);
            }
        });
        OptionsMenu.add(SetttingsMenu);

        MenuBar.add(OptionsMenu);

        DebugMenu.setText("Debug");

        EnterDebugger.setText("Enter Debugger");
        EnterDebugger.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                EnterDebuggerActionPerformed(evt);
            }
        });
        DebugMenu.add(EnterDebugger);

        EnterMemoryViewer.setText("Memory viewer");
        EnterMemoryViewer.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                EnterMemoryViewerActionPerformed(evt);
            }
        });
        DebugMenu.add(EnterMemoryViewer);

        ToggleConsole.setText("Toggle Console");
        ToggleConsole.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                ToggleConsoleActionPerformed(evt);
            }
        });
        DebugMenu.add(ToggleConsole);

        ElfHeaderViewer.setText("Elf Header Info");
        ElfHeaderViewer.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                ElfHeaderViewerActionPerformed(evt);
            }
        });
        DebugMenu.add(ElfHeaderViewer);

        InstructionCounter.setText("Instruction Counter");
        InstructionCounter.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                InstructionCounterActionPerformed(evt);
            }
        });
        DebugMenu.add(InstructionCounter);

        MenuBar.add(DebugMenu);

        HelpMenu.setText("Help");

        About.setText("About");
        About.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                AboutActionPerformed(evt);
            }
        });
        HelpMenu.add(About);

        MenuBar.add(HelpMenu);

        setJMenuBar(MenuBar);

        pack();
    }// </editor-fold>//GEN-END:initComponents

private void ToggleConsoleActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_ToggleConsoleActionPerformed
    if (!consolewin.isVisible()) {
        mainwindowPos = this.getLocation();

        if (snapConsole)
            consolewin.setLocation(mainwindowPos.x, mainwindowPos.y + getHeight());
    }
    consolewin.setVisible(!consolewin.isVisible());
}//GEN-LAST:event_ToggleConsoleActionPerformed

private void EnterDebuggerActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_EnterDebuggerActionPerformed
    if (Settings.get_instance().readBoolOptions("emuoptions/recompiler"))
        return;
    if(disasm==null)
     {
      PauseEmu();
      disasm = new DisassemblerFrame(emulator);
      int pos[] = Settings.get_instance().readWindowPos("disassembler");
      disasm.setLocation(pos[0], pos[1]);
      disasm.setVisible(true);
      emulator.setDebugger(disasm);
     }
     else
     {
         disasm.setVisible(true);
         disasm.RefreshDebugger();
     }
}//GEN-LAST:event_EnterDebuggerActionPerformed

private void RunButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_RunButtonActionPerformed
            RunEmu();
}//GEN-LAST:event_RunButtonActionPerformed
 private JFileChooser makeJFileChooser() {
        final JFileChooser fc = new JFileChooser();
        fc.setDialogTitle("Open Elf/Pbp File");
        fc.setCurrentDirectory(new java.io.File("."));
        return fc;
    }

private void OpenFileActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_OpenFileActionPerformed
        PauseEmu();
        if(consolewin!=null)
          consolewin.clearScreenMessages();

    final JFileChooser fc = makeJFileChooser();
    int returnVal = fc.showOpenDialog(this);

    if (userChooseSomething(returnVal)) {
        File file = fc.getSelectedFile();
        loadFile(file);
    } else {
        return; //user cancel the action

    }
}//GEN-LAST:event_OpenFileActionPerformed

public void loadFile(File file) {
	//This is where a real application would open the file.
	try {
	   //emulator.load(file.getPath());
	   // Create a read-only memory-mapped file
	    FileChannel roChannel = new RandomAccessFile(file, "r").getChannel();
	    ByteBuffer readbuffer = roChannel.map(FileChannel.MapMode.READ_ONLY, 0, (int)roChannel.size());
	    emulator.load(readbuffer);
	    String findpath = file.getParent();
	    //System.out.println(findpath);
	    pspiofilemgr.get_instance().setfilepath(findpath);
	    this.setTitle(version + " - " + file.getName());
	} catch (IOException e) {
	    e.printStackTrace();
	    JpcspDialogManager.showError(this, "IO Error : " + e.getMessage());
	} catch (Exception ex) {
	    ex.printStackTrace();
	    JpcspDialogManager.showError(this, "Critical Error : " + ex.getMessage());
	}
}

private void PauseButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_PauseButtonActionPerformed
    TogglePauseEmu();
}//GEN-LAST:event_PauseButtonActionPerformed

private void ElfHeaderViewerActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_ElfHeaderViewerActionPerformed
     if(elfheader==null)
     {

      elfheader = new ElfHeaderInfo();
      int pos[] = Settings.get_instance().readWindowPos("elfheader");
      elfheader.setLocation(pos[0], pos[1]);
      elfheader.setVisible(true);
     }
     else
     {
       elfheader.RefreshWindow();
       elfheader.setVisible(true);
     }
}//GEN-LAST:event_ElfHeaderViewerActionPerformed

private void EnterMemoryViewerActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_EnterMemoryViewerActionPerformed
    PauseEmu();
    if(memoryview==null)
     {

      memoryview = new MemoryViewer();
      int pos[] = Settings.get_instance().readWindowPos("memoryview");
      memoryview.setLocation(pos[0], pos[1]);
      memoryview.setVisible(true);
      emulator.setMemoryViewer(memoryview);
     }
     else
     {
       memoryview.RefreshMemory();
       memoryview.setVisible(true);
     }
}//GEN-LAST:event_EnterMemoryViewerActionPerformed

private void AboutActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_AboutActionPerformed
  StringBuilder message = new StringBuilder();
    message.append("<html>").append("<h2>" + MetaInformation.FULL_NAME + "</h2>").append("<hr/>").append("Official site      : <a href='" + MetaInformation.OFFICIAL_SITE + "'>" + MetaInformation.OFFICIAL_SITE + "</a><br/>").append("Official forum     : <a href='" + MetaInformation.OFFICIAL_FORUM + "'>" + MetaInformation.OFFICIAL_FORUM + "</a><br/>").append("Official repository: <a href='" + MetaInformation.OFFICIAL_REPOSITORY + "'>" + MetaInformation.OFFICIAL_REPOSITORY + "</a><br/>").append("<hr/>").append("<i>Team:</i> <font color='gray'>" + MetaInformation.TEAM + "</font>").append("</html>");
    JOptionPane.showMessageDialog(this, message.toString(), version, JOptionPane.INFORMATION_MESSAGE);
}//GEN-LAST:event_AboutActionPerformed

private void RunEmuActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_RunEmuActionPerformed
   RunEmu();
}//GEN-LAST:event_RunEmuActionPerformed

private void PauseEmuActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_PauseEmuActionPerformed
  PauseEmu();
}//GEN-LAST:event_PauseEmuActionPerformed

private void SetttingsMenuActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_SetttingsMenuActionPerformed

    if(setgui==null)
     {

      setgui = new SettingsGUI();
      Point mainwindow = this.getLocation();
      setgui.setLocation(mainwindow.x+100, mainwindow.y+50);
      setgui.setVisible(true);

      /* add a direct link to the controller and main window*/
      setgui.setController(emulator.getController());
      setgui.setMainGUI(this);
     }
     else
     {
       setgui.RefreshWindow();
       setgui.setVisible(true);
     }
}//GEN-LAST:event_SetttingsMenuActionPerformed

private void ExitEmuActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_ExitEmuActionPerformed
    exitEmu();
}//GEN-LAST:event_ExitEmuActionPerformed

private void OpenMemStickActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_OpenMemStickActionPerformed
    PauseEmu();
    if(consolewin!=null)
          consolewin.clearScreenMessages();
    if(memstick==null)
     {

      memstick = new MemStickBrowser(this, new File("ms0/PSP/GAME"));
      Point mainwindow = this.getLocation();
      memstick.setLocation(mainwindow.x+100, mainwindow.y+50);
      memstick.setVisible(true);
    }
    else
    {
      memstick.refreshFiles();
      memstick.setVisible(true);
    }

}//GEN-LAST:event_OpenMemStickActionPerformed

private void formWindowClosing(java.awt.event.WindowEvent evt) {//GEN-FIRST:event_formWindowClosing
    exitEmu();
}//GEN-LAST:event_formWindowClosing

private void openUmdActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_openUmdActionPerformed
        PauseEmu();//GEN-LAST:event_openUmdActionPerformed
       if(consolewin!=null)
          consolewin.clearScreenMessages();
   if (Settings.get_instance().readBoolOptions("emuoptions/umdbrowser"))
   {
      if(umdbrowser==null)
      {
      
      umdbrowser = new UmdBrowser(this, new File(Settings.get_instance().readStringOptions("emuoptions/umdpath") + "/"));
      Point mainwindow = this.getLocation();
      umdbrowser.setLocation(mainwindow.x+100, mainwindow.y+50);
      umdbrowser.setVisible(true);
     }
     else
     {
      umdbrowser.refreshFiles();
      umdbrowser.setVisible(true);
     } 
   }
   else
   {
    final JFileChooser fc = makeJFileChooser();
    fc.setDialogTitle("Open umd iso");
    int returnVal = fc.showOpenDialog(this);
    
    if (userChooseSomething(returnVal)) {
        File file = fc.getSelectedFile();      
        loadUMD(file);
    } else {
        return; //user cancel the action
    }
   }
}

public void loadUMD(File file) {
	try {
	    UmdIsoReader iso = new UmdIsoReader(file.getPath());
	    UmdIsoFile paramSfo = iso.getFile("PSP_GAME/param.sfo");
	    
	    System.out.println("---- Loading param.sfo from UMD ----");
	    PSF params = new PSF(0);
	    byte[] sfo = new byte[(int)paramSfo.length()];
	    paramSfo.read(sfo);
	    ByteBuffer buf = ByteBuffer.wrap(sfo);
	    params.read(buf);
	    System.out.println(params);
	    System.out.println("------------------------------------");
	    
	    UmdIsoFile bootBin = iso.getFile("PSP_GAME/SYSDIR/boot.bin");
	    byte[] bootfile = new byte[(int)bootBin.length()];
	    bootBin.read(bootfile);
	    ByteBuffer buf1 = ByteBuffer.wrap(bootfile);
	    emulator.load(buf1);
	  
	} catch (IOException e) {
	    e.printStackTrace();
	    JpcspDialogManager.showError(this, "IO Error : " + e.getMessage());
	} catch (Exception ex) {
	    ex.printStackTrace();
	    JpcspDialogManager.showError(this, "Critical Error : " + ex.getMessage());
	}
}

private void ResetEmuActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_ResetEmuActionPerformed
// TODO add your handling code here:
}//GEN-LAST:event_ResetEmuActionPerformed

private void ResetButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_ResetButtonActionPerformed
// TODO add your handling code here:
}//GEN-LAST:event_ResetButtonActionPerformed

private void InstructionCounterActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_InstructionCounterActionPerformed
    if(instructioncounter==null)
     {
      PauseEmu();
      instructioncounter = new InstructionCounter(emulator);
      Point mainwindow = this.getLocation();
      instructioncounter.setLocation(mainwindow.x+100, mainwindow.y+50);
      instructioncounter.setVisible(true);
     }
     else
     {
         instructioncounter.setVisible(true);
         instructioncounter.RefreshWindow();
     }
}//GEN-LAST:event_InstructionCounterActionPerformed



private void exitEmu() {
    if (Settings.get_instance().readBoolOptions("guisettings/saveWindowPos"))
        Settings.get_instance().writeWindowPos("mainwindow", getLocation());
    Settings.get_instance().writeBoolOptions("guisettings/snapLogwindow", snapConsole);

    System.exit(0);
}

public void snaptoMainwindow() {
    snapConsole = true;
    mainwindowPos = getLocation();
    consolewin.setLocation(mainwindowPos.x, mainwindowPos.y + getHeight());
}

private void RunEmu()
{
    emulator.RunEmu();
}
private void TogglePauseEmu()
{
    // This is a toggle, so can pause and unpause
    if (emulator.run)
    {
        if (!emulator.pause)
            emulator.PauseEmu();
        else
            RunEmu();
    }
}
private void PauseEmu()
{
    // This will only enter pause mode
    if (emulator.run && !emulator.pause) {
        emulator.PauseEmu();
    }
}
public void RefreshButtons()
{
    RunButton.setSelected(emulator.run && !emulator.pause);
    PauseButton.setSelected(emulator.run && emulator.pause);
}
public void setMainTitle(String message)
{
     String oldtitle = getTitle();
     int sub = oldtitle.indexOf("average");
     if(sub!=-1)
     {
      String newtitle= oldtitle.substring(0, sub-1);
      setTitle(newtitle + " " + message);
     }
     else
     {
         setTitle(oldtitle + " " + message);
     }
}
    /**
    * @param args the command line arguments
    */
    public static void main(String args[]) {
        try {
            UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
        } catch (Exception e) {
            e.printStackTrace();
        }
        java.awt.EventQueue.invokeLater(new Runnable() {
            @Override
            public void run() {
                MainGUI maingui = new MainGUI();
                maingui.setVisible(true);
                if (Settings.get_instance().readBoolOptions("guisettings/openLogwindow"))
                    maingui.consolewin.setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JMenuItem About;
    private javax.swing.JMenu DebugMenu;
    private javax.swing.JMenuItem ElfHeaderViewer;
    private javax.swing.JMenu EmulationMenu;
    private javax.swing.JMenuItem EnterDebugger;
    private javax.swing.JMenuItem EnterMemoryViewer;
    private javax.swing.JMenuItem ExitEmu;
    private javax.swing.JMenu FileMenu;
    private javax.swing.JMenu HelpMenu;
    private javax.swing.JMenuItem InstructionCounter;
    private javax.swing.JMenuBar MenuBar;
    private javax.swing.JMenuItem OpenFile;
    private javax.swing.JMenuItem OpenMemStick;
    private javax.swing.JMenu OptionsMenu;
    private javax.swing.JToggleButton PauseButton;
    private javax.swing.JMenuItem PauseEmu;
    private javax.swing.JButton ResetButton;
    private javax.swing.JMenuItem ResetEmu;
    private javax.swing.JToggleButton RunButton;
    private javax.swing.JMenuItem RunEmu;
    private javax.swing.JMenuItem SetttingsMenu;
    private javax.swing.JMenuItem ToggleConsole;
    private javax.swing.JToolBar jToolBar1;
    private javax.swing.JMenuItem openUmd;
    // End of variables declaration//GEN-END:variables
    private boolean userChooseSomething(int returnVal) {
        return returnVal == JFileChooser.APPROVE_OPTION;
    }

    @Override
    public void keyTyped(KeyEvent arg0) { }

    @Override
    public void keyPressed(KeyEvent arg0) {
        emulator.getController().keyPressed(arg0);
    }

    @Override
    public void keyReleased(KeyEvent arg0) {
        emulator.getController().keyReleased(arg0);
    }

    @Override
    public void componentHidden(ComponentEvent e) { }

    @Override
    public void componentMoved(ComponentEvent e) {
        if (snapConsole && consolewin.isVisible()) {
            Point newPos = this.getLocation();
            Point consolePos = consolewin.getLocation();
            Dimension mainwindowSize = this.getSize();

            if (consolePos.x == mainwindowPos.x &&
                consolePos.y == mainwindowPos.y + mainwindowSize.height) {
                consolewin.setLocation(newPos.x, newPos.y + mainwindowSize.height);
            } else {
                snapConsole = false;
            }

            mainwindowPos = newPos;
        }
    }

    @Override
    public void componentResized(ComponentEvent e) { }

    @Override
    public void componentShown(ComponentEvent e) { }
}
