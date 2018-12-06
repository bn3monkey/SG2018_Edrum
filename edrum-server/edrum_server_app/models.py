from django.db import models

from django.contrib.auth.models import AbstractBaseUser
from django.contrib.auth.models import BaseUserManager
from django.dispatch import receiver

from rest_framework.authtoken.models import Token

# Create your models here.
class NoteFileModel(models.Model):
    server_id = models.AutoField(primary_key = True)
    name = models.CharField(max_length=50,default='')
    artist = models.CharField(max_length=50,default='')
    date = models.DateField(auto_now=False,auto_now_add=True)
    ID = models.CharField(max_length=20,default='')
    song = models.FileField(null=True)

    class Meta:
        ordering = ('server_id',)

# is that true?

class UserManager(BaseUserManager):
    def create_user(self,user_id,password=None):
        user=self.model(user_id=user_id)
        user.set_password(password)
        user.save(using=self._db)
        return user

    def create_superuser(self,user_id,password=None):
        user = self.model(user_id=user_id)
        user.is_admin = True
        user.is_active = True
        user.set_password(password)
        user.save(using=self._db)
        return user

class User(AbstractBaseUser):
    user_id = models.CharField(primary_key=True,max_length=20)

    is_active = models.BooleanField(default=False)
    is_admin = models.BooleanField(default=False)

    USERNAME_FIELD='user_id'
    objects = UserManager()

    @property
    def is_staff(self):
        return self.is_admin

    #@receiver(post_save, sender=settings.AUTH_USER_MODEL)
    def create_auth_token(sender, instance = None, created = False, **kwargs):
	    if created:
		    Token.objects.create(user=instance)
