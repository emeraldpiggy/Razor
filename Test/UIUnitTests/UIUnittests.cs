using NUnit.Framework;
using RazorUI;

namespace UIUnitTests
{
    [TestFixture]
    public class UiTests
    {
        [SetUp]
        public void Setup()
        {
            
        }

        [TearDown]
        public void TearDown()
        {
            
        }

        [Test]
        public void If_geturiFromCore_should_display()
        {

            //Arrange
            var mainwindow = new MainWindow();

            //Act
            string res = mainwindow.GetScheme();

            //Assert
            Assert.AreEqual("Wrong Uri",res);
        }
    }
}
